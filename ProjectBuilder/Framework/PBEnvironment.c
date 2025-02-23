// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#include <sys/stat.h>
#include <copyfile.h>

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
    PBProjectRef _currentProject;
};

CFBooleanRef PBEnvironmentSetupWorkingDirectories(PBEnvironmentRef env) {
    if (env->_buildRootUUID == NULL) {
        return kCFBooleanFalse;
    }
    
    if (open(CFStringGetCStringPtr(env->_buildRootDirectory, kCFStringEncodingASCII), O_RDONLY) == -1) {
        mkpath_np(CFStringGetCStringPtr(env->_buildRootDirectory, kCFStringEncodingASCII), 755);
        
    }
    
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
        
        env->_buildRootUUID = CFUUIDCreate(kCFAllocatorDefault);
        
        CFStringRef str = CFUUIDCreateString(kCFAllocatorDefault, env->_buildRootUUID);
        CFMutableStringRef mutable = CFStringCreateMutable(kCFAllocatorDefault, CFStringGetLength(str) + CFStringGetLength(args->buildRootDirectory));
        
        return env;
    }
    return NULL;
}
