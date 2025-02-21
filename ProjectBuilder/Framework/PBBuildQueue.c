// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#include <ProjectBuilder/PBBuildQueue.h>
#include <ProjectBuilder/PBRuntime.h>

#include "Private/__PBBuildQueue.h"

struct _PBBuildQueue {
    struct __PBRuntime rt;
    
    CFArrayRef _sortedQueue; // The parser should sort each project
    CFDictionaryRef _projectMap;
};

PBProjectRef __PBBQFindProjectInMap(PBBuildQueueRef bq, CFStringRef name) {
    if (bq->_projectMap == NULL) {
        return NULL;
    } else {
        // It 100% should be a PBProj object.
        // how do i properly integrate with CF ffs
        PBProjectRef proj = (PBProjectRef)CFDictionaryGetValue(bq->_projectMap, name);
        return proj;
    }
    return NULL;
}

bool __PBBQBuild(PBBuildQueueRef bq, PBProjectRef proj) {
    return true;
}
