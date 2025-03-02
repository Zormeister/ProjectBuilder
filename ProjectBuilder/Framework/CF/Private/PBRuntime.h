// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#ifndef PROJECTBUILDER_PRIVATE_PBRUNTIME_H
#define PROJECTBUILDER_PRIVATE_PBRUNTIME_H

// where else can i get UInt32 and those nice looking types from
#include <sys/stat.h>
#include <MacTypes.h>

#include <CoreFoundation/CoreFoundation.h>

typedef void (*PBRuntimeFinalize)(void *);

// Just so we know it's OUR object.
#define PBRT_MAGIC 'PBRT'

struct __PBRuntime {
    UInt32 Magic;
    UInt32 RetainCount;
    UInt32 TypeID;
    PBRuntimeFinalize Finalize;
};

static bool DirectoryExists(const char *dirPath) {
    struct stat s;
    if (stat(dirPath, &s) == 0 && S_ISDIR(s.st_mode)) {
        return true;
    } else {
        return false;
    }
}

static bool DirectoryExistsCF(CFStringRef cf) {
    struct stat s;
    if (stat(CFStringGetCStringPtr(cf, kCFStringEncodingASCII), &s) == 0 && S_ISDIR(s.st_mode)) {
        return true;
    } else {
        return false;
    }
}

static void CreateDirectory(const char *path) {
    mkpath_np(path, 0755); // hopefully it expects the octal format???
}

#endif /* PROJECTBUILDER_PRIVATE_PBRUNTIME_H */
