// Copyright (C) 2024-2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause license.

#include "ProjectBuilder.h"
#include <os/log.h>
#include "PBConstants.h"
#include "Private/PBRuntime.h"

struct _PBManifest {
    struct __PBRuntime _runtime;
    /* Config */
    CFBooleanRef _abortOnError;
    
    /* Projects */
    CFArrayRef _projects;

    CFDictionaryRef _plistRoot;
};

void _PBManifestFinalize(void *mfst) {
    PBManifestRef manifest = (PBManifestRef)mfst;
    
    /* clean variables we have */
    CFRelease(manifest->_abortOnError);
    CFRelease(manifest->_plistRoot);
    CFRelease(manifest->_projects);
    
    /* delete ourself */
    CFAllocatorDeallocate(kCFAllocatorDefault, manifest);
}

bool _PBManifestUnpackPlist(PBManifestRef self, CFDictionaryRef dict) {
    CFArrayRef projArr = (CFArrayRef)CFDictionaryGetValue(dict, kPBManifestProjectsKey);
    if (CFGetTypeID(projArr) != CFArrayGetTypeID()) {
        os_log_error(OS_LOG_DEFAULT, "Failed to unpack Manifest: Invalid Property List.\n");
        return false;
    }

    if (CFDictionaryContainsKey(dict, kPBManifestConfigKey)) {
        CFDictionaryRef cfg = (CFDictionaryRef)CFDictionaryGetValue(dict, kPBManifestConfigKey);
        if (CFGetTypeID(cfg) != CFDictionaryGetTypeID()) {
            os_log_error(OS_LOG_DEFAULT, "Failed to unpack Manifest: Bad Config section.\n");
        } else {
            CFDictionaryContainsKey(cfg, kPBManifestExternalRepositoryCommitSHAKey);
        }
    }
    self->_abortOnError = kCFBooleanTrue;

    return true;
}

/* ObjC port when */

PBManifestRef PBManifestCreateWithPropertyList(CFPropertyListRef propertyList) {
    if (CFGetTypeID(propertyList) == CFDictionaryGetTypeID()) {
        PBManifestRef manifest = (PBManifestRef)CFAllocatorAllocate(kCFAllocatorDefault, sizeof(struct _PBManifest), 0);
        manifest->_runtime.Magic = PBRT_MAGIC;
        manifest->_runtime.TypeID = 1;
        manifest->_runtime.Finalize = &_PBManifestFinalize;
        CFDictionaryRef dict = (CFDictionaryRef)propertyList;
        manifest->_plistRoot = dict;
        if (CFDictionaryContainsKey(dict, CFSTR("Projects")) == false) {
            CFAllocatorDeallocate(kCFAllocatorDefault, manifest);
            os_log_error(OS_LOG_DEFAULT, "Failed to create Manifest: Invalid Property List.\n");
            return NULL;
        } else {
            if (_PBManifestUnpackPlist(manifest, dict)) {
                CFShow(dict);
                return manifest;
            } else {
                os_log_error(OS_LOG_DEFAULT, "Failed to create Manifest: Failed to unpack plist.\n");
                CFAllocatorDeallocate(kCFAllocatorDefault, manifest);
                return NULL;
            }
        }
    } else {
        os_log_error(OS_LOG_DEFAULT, "Failed to create Manifest: CFPropertyList does not conform to CFDictionary\n");
    }
    return NULL;
}
