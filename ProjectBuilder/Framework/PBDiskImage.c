// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#include "PBDiskImage.h"
#include "PBConstants.h"

#include "Private/PBRuntime.h"

#define PBDI_TRACE 1

#ifdef PBDI_TRACE
#define TRACE_BEGIN fprintf(stdout, "[PBDiskImage]: %s >>", __PRETTY_FUNCTION__);
#define TRACE_END fprintf(stdout, "[PBDiskImage]: %s >>", __PRETTY_FUNCTION__);
#else
#define TRACE_BEGIN while (0) {};
#define TRACE_END while (0) {};
#endif

struct _PBDiskImage {
    struct __PBRuntime rt;
    
    // our data
    CFStringRef _buildRootsPath; // will spit the DMG into <BuildRootsDirectory>/DiskImages/<BuildRootUUID>.dmg
    CFNumberRef _imageSize;
    CFStringRef _imageType;
    CFStringRef _volumeName;
    CFStringRef _imageLayout;
    CFStringRef _volumeFSName;
    CFStringRef _buildRootUUIDString;
    CFBooleanRef _didCreateImage;
    CFBooleanRef _isMounted;
};

void DiskImageFinalize(void *i) {
    TRACE_BEGIN
    PBDiskImageRef img = (PBDiskImageRef)i;
    
    /* clean variables we have */
    if (img->_buildRootsPath != NULL) {
        CFRelease(img->_buildRootsPath);
    }
    
    if (img->_imageSize != NULL) {
        CFRelease(img->_imageSize);
        CFRelease(img->_imageType);
        CFRelease(img->_imageLayout);
        CFRelease(img->_volumeName);
        CFRelease(img->_volumeFSName);
        CFRelease(img->_buildRootUUIDString);
        img->_didCreateImage = NULL;
        img->_isMounted = NULL;
    }
    
    /* delete ourself */
    CFAllocatorDeallocate(kCFAllocatorDefault, img);
    TRACE_END
}

CFBooleanRef _PBDiskImageFetchData(PBDiskImageRef img, CFDictionaryRef imgInfo) {
    TRACE_BEGIN
    if (img == NULL && imgInfo == NULL) {
        fprintf(stderr, "[PBDiskImage]: what?\n");
        TRACE_END
        return kCFBooleanFalse;
    }

    if (!CFDictionaryContainsKey(imgInfo, kPBDiskImageDiskSizeKey)) {
        fprintf(stderr, "[PBDiskImage]: No DMG size key in image info\n");
        TRACE_END
        return kCFBooleanFalse;
    } else {
        CFNumberRef val = (CFNumberRef)CFDictionaryGetValue(imgInfo, kPBDiskImageDiskSizeKey);
        if (CFGetTypeID(val) == CFNumberGetTypeID()) {
            img->_imageSize = val;
        }
    }
    
    if (!CFDictionaryContainsKey(imgInfo, kPBDiskImageDiskLayoutKey)) {
        /* Default to GPTSPUD if unspecified */
        img->_imageLayout = CFStringCreateWithCString(kCFAllocatorDefault, "GPTSPUD", kCFStringEncodingASCII);
    } else {
        CFStringRef val = (CFStringRef)CFDictionaryGetValue(imgInfo, kPBDiskImageDiskLayoutKey);
        if (CFGetTypeID(val) == CFStringGetTypeID()) {
            img->_imageLayout = val;
        }
    }
    
    if (!CFDictionaryContainsKey(imgInfo, kPBDiskImageFileSystemKey)) {
        /* Default to Journaled HFS+ if unspecified */
        img->_volumeFSName = CFStringCreateWithCString(kCFAllocatorDefault, "Journaled HFS+", kCFStringEncodingASCII);
    } else {
        CFStringRef val = (CFStringRef)CFDictionaryGetValue(imgInfo, kPBDiskImageFileSystemKey);
        if (CFGetTypeID(val) == CFStringGetTypeID()) {
            img->_volumeFSName = val;
        }
    }
    
    if (!CFDictionaryContainsKey(imgInfo, kPBDiskImageDiskTypeKey)) {
        /* Default to UDIF if unspecified */
        img->_imageType = CFStringCreateWithCString(kCFAllocatorDefault, "UDIF", kCFStringEncodingASCII);
    } else {
        CFStringRef val = (CFStringRef)CFDictionaryGetValue(imgInfo, kPBDiskImageDiskTypeKey);
        if (CFGetTypeID(val) == CFStringGetTypeID()) {
            img->_imageType = val;
        }
    }

    if (!CFDictionaryContainsKey(imgInfo, kPBDiskImageVolumeNameKey)) {
        img->_volumeName = img->_buildRootUUIDString;
    } else {
        CFStringRef val = (CFStringRef)CFDictionaryGetValue(imgInfo, kPBDiskImageVolumeNameKey);
        if (CFGetTypeID(val) == CFStringGetTypeID()) {
            img->_volumeName = val;
        }
    }
    
    img->_didCreateImage = kCFBooleanFalse;
    img->_isMounted = kCFBooleanFalse;
    
    TRACE_END
    return kCFBooleanTrue;
}

PBDiskImageRef PBDiskImageCreate(CFStringRef buildRootsPath, CFUUIDRef buildRootUUID, CFDictionaryRef diskImageInfo) {
    TRACE_BEGIN
    if (buildRootsPath != NULL && diskImageInfo != NULL) {
        PBDiskImageRef img = (PBDiskImageRef)CFAllocatorAllocate(kCFAllocatorDefault, sizeof(struct _PBDiskImage), 0);
        img->rt.Magic = PBRT_MAGIC;
        img->rt.TypeID = 3; /* TBH is the TypeID field even going to be used? */
        img->rt.Finalize = DiskImageFinalize;
        
        img->_buildRootUUIDString = CFUUIDCreateString(kCFAllocatorDefault, buildRootUUID);
        img->_buildRootsPath = CFStringCreateCopy(kCFAllocatorDefault, buildRootsPath);
        if (_PBDiskImageFetchData(img, diskImageInfo) == kCFBooleanFalse) {
            fprintf(stderr, "[PBDiskImage]: Something went wrong - consult the last stderr message.\n");
            DiskImageFinalize(img);
            CFAllocatorDeallocate(kCFAllocatorDefault, img);
            return NULL;
        }
        
        TRACE_END
        return img;
    }
    TRACE_END
    return NULL;
}

/* Holy SHIT I wish I had bindings for DiskImages.framework... */
CFBooleanRef PBDiskImageCreateImage(PBDiskImageRef img) {
    TRACE_BEGIN
    
    if (img->_didCreateImage == kCFBooleanTrue) {
        fprintf(stdout, "[PBDiskImage]: That's weird. Someone called %s twice.\n", __FUNCTION__);
        return kCFBooleanTrue;
    }
    
    CFMutableStringRef cf = CFStringCreateMutableCopy(kCFAllocatorMalloc, CFStringGetLength(img->_buildRootsPath) + strlen("/DiskImages"), img->_buildRootsPath);
    CFStringAppend(cf, CFSTR("/DiskImages"));

    if (DirectoryExistsCF(cf) == false) {
        CreateDirectory(CFStringGetCStringPtr(cf, kCFStringEncodingASCII));
    }

    /* Start by getting the combined length of our strings. */
    /* Probably allocates more than I need, doesn't really fuss me because it's temporary and gets discarded. */
    size_t size = CFStringGetLength(img->_imageType)
                + CFStringGetLength(img->_imageLayout)
                + CFStringGetLength(img->_imageLayout)
                + CFStringGetLength(img->_volumeName)
                + CFStringGetLength(img->_volumeFSName)
                + CFNumberGetByteSize(img->_imageSize)
                + CFStringGetLength(cf)
                + CFStringGetLength(img->_buildRootUUIDString)
                + strlen("hdiutil create ")
                + strlen(" -volname %s")
                + strlen(" -layout %s")
                + strlen(" -size %s")
                + strlen(" -type %s")
                + strlen(" -fs %s");

    char *tmp = malloc(size);
    int ntmp;
    CFNumberGetValue(img->_imageSize, kCFNumberIntType, &ntmp);
    snprintf(tmp, size, "hdiutil create -layout %s -size %dm -type %s -fs %s -volname %s %s/%s.dmg",
             CFStringGetCStringPtr(img->_imageLayout, kCFStringEncodingASCII),
             ntmp,
             CFStringGetCStringPtr(img->_imageType, kCFStringEncodingASCII),
             CFStringGetCStringPtr(img->_volumeFSName, kCFStringEncodingASCII),
             CFStringGetCStringPtr(img->_volumeName, kCFStringEncodingASCII),
             CFStringGetCStringPtr(cf, kCFStringEncodingASCII),
             CFStringGetCStringPtr(img->_buildRootUUIDString, kCFStringEncodingASCII));

    fprintf(stdout, "[PBDiskImage]: Executing... (%s)", tmp);
    int res;
    if ((res = system(tmp))) {
        fprintf(stderr, "[PBDiskImage]: FAIL. (%d)", res);
        CFRelease(cf);
        free(tmp);
        TRACE_END
        return kCFBooleanFalse;
    }

    img->_didCreateImage = kCFBooleanTrue;
    CFRelease(cf);
    free(tmp);
    TRACE_END
    return kCFBooleanTrue;
}

CFBooleanRef PBDiskImageAttachImage(PBDiskImageRef img) {
    TRACE_BEGIN

    if (img->_isMounted == kCFBooleanTrue) {
        fprintf(stdout, "[PBDiskImage]: That's weird. Someone called %s twice.\n", __FUNCTION__);
        return kCFBooleanTrue;
    }

    CFMutableStringRef cf = CFStringCreateMutableCopy(kCFAllocatorMalloc, CFStringGetLength(img->_buildRootsPath) + strlen("/DiskImages/") + CFStringGetLength(img->_buildRootUUIDString), img->_buildRootsPath);
    CFStringAppend(cf, CFSTR("/DiskImages/"));

    /* Start by getting the combined length of our strings. */
    /* Probably allocates more than I need, doesn't really fuss me because it's temporary and gets discarded. */
    /* Our build controller should have already created our BuildRoot path */
    size_t size = CFStringGetLength(cf)
                + CFStringGetLength(img->_buildRootUUIDString) // once for the DMG name
                + CFStringGetLength(img->_buildRootUUIDString) // twice for the mount path
                + CFStringGetLength(img->_buildRootsPath) // twice for the mount path
                + strlen("%s.dmg") // add space for our DMG
                + strlen("hdiutil attach %s")
                + strlen(" -mountpoint %s");

    char *tmp = malloc(size);

    snprintf(tmp, size, "hdiutil attach %s%s.dmg %s%s",
             CFStringGetCStringPtr(cf, kCFStringEncodingASCII),
             CFStringGetCStringPtr(img->_buildRootUUIDString, kCFStringEncodingASCII),
             CFStringGetCStringPtr(img->_buildRootsPath, kCFStringEncodingASCII),
             CFStringGetCStringPtr(img->_buildRootUUIDString, kCFStringEncodingASCII));

    fprintf(stdout, "[PBDiskImage]: Executing... (%s)", tmp);
    int res;
    if ((res = system(tmp))) {
        fprintf(stderr, "[PBDiskImage]: FAIL. (%d)", res);
        CFRelease(cf);
        free(tmp);
        TRACE_END
        return kCFBooleanFalse;
    }

    img->_isMounted = kCFBooleanTrue;
    CFRelease(cf);
    free(tmp);
    TRACE_END
    return kCFBooleanTrue;
}

/* Since Tiger hdiutil accepts the mount path for a DMG as a way to detach it. */
CFBooleanRef PBDiskImageDetachImage(PBDiskImageRef img) {
    TRACE_BEGIN

    if (img->_isMounted == kCFBooleanFalse) {
        fprintf(stdout, "[PBDiskImage]: That's weird. Someone called %s twice.\n", __FUNCTION__);
        return kCFBooleanTrue;
    }

    /* Start by getting the combined length of our strings. */
    /* Probably allocates more than I need, doesn't really fuss me because it's temporary and gets discarded. */
    /* Our build controller should have already created our BuildRoot path */
    size_t size = CFStringGetLength(img->_buildRootUUIDString) // twice for the mount path
                + CFStringGetLength(img->_buildRootsPath) // we need this
                + strlen("hdiutil detach %s%s");

    char *tmp = malloc(size);

    snprintf(tmp, size, "hdiutil detach %s%s",
             CFStringGetCStringPtr(img->_buildRootsPath, kCFStringEncodingASCII),
             CFStringGetCStringPtr(img->_buildRootUUIDString, kCFStringEncodingASCII));

    fprintf(stdout, "[PBDiskImage]: Executing... (%s)", tmp);
    int res;
    if ((res = system(tmp))) {
        fprintf(stderr, "[PBDiskImage]: FAIL. (%d)", res);
        free(tmp);
        TRACE_END
        return kCFBooleanFalse;
    }

    img->_isMounted = kCFBooleanFalse;

    free(tmp);
    TRACE_END
    return kCFBooleanTrue;
}
