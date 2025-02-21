// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#include "PBEnvironment.h"

#include "Private/PBRuntime.h"

struct _PBEnvironment {
    struct __PBRuntime rt;
    
    /* our stuff */
    CFDictionaryRef _shellArgs;
    CFStringRef _buildRootDirectory;
    CFStringRef _sdkRoot;
    CFUUIDRef _buildRootUUID;
    CFBooleanRef _setsXBSVariables;
    CFBooleanRef _selfReliant;
};

CFBooleanRef PBEnvironmentSetupWorkingDirectories(PBEnvironmentRef env) {
    if (env->_buildRootUUID == NULL) {
        return kCFBooleanFalse;
    }
    
    CFStringRef current;
    return kCFBooleanTrue;
}

void EnvironmentFinalise(void *e) {
    PBEnvironmentRef env = (PBEnvironmentRef)e;
    
    /* clean variables we have */
    CFRelease(env->_shellArgs);
    CFRelease(env->_buildRootDirectory);
    CFRelease(env->_buildRootUUID);
    CFRelease(env->_sdkRoot);
    
    /* delete ourself */
    CFAllocatorDeallocate(kCFAllocatorDefault, env);
}

PBEnvironmentRef PBEnvironmentCreateWithArgs(PBEnvironmentArgs *args) {
    if (args != NULL) {
        PBEnvironmentRef env = (PBEnvironmentRef)CFAllocatorAllocate(kCFAllocatorDefault, sizeof(struct _PBEnvironment), 0);
        env->rt.Magic = PBRT_MAGIC;
        env->rt.TypeID = 2;
        env->rt.Finalize = EnvironmentFinalise;
    }
    return NULL;
}
