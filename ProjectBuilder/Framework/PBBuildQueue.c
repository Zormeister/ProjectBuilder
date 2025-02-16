// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#include <AssertMacros.h>

#include <ProjectBuilder/PBBuildQueue.h>
#include <ProjectBuilder/PBRuntime.h>

#include "Private/__PBBuildQueue.h"

struct _PBBuildQueue {
    struct __PBRuntime rt;
    
    CFArrayRef _sortedQueue; // The parser should sort each project
    CFDictionaryRef _projectMap;
};

PBProjectRef __PBBQFindProjectInMap(PBBuildQueueRef bq, CFStringRef name) {
    __Require_String(bq->_projectMap != NULL, fail_gracefully, "");
    
fail_gracefully:
    return NULL;
}
