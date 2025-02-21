// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#include "Private/PBRuntime.h"
#include "PBExternalRepository.h"

struct _PBExternalRepository {
    struct __PBRuntime rt;
    
    CFURLRef _repoURL;
    CFStringRef _repoName;
    CFStringRef _repoTag;
};
