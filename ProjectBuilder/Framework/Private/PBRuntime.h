// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#ifndef PROJECTBUILDER_PRIVATE_PBRUNTIME_H
#define PROJECTBUILDER_PRIVATE_PBRUNTIME_H

// where else can i get UInt32 and those nice looking types from
#include <MacTypes.h>

typedef void (*PBRuntimeFinalize)(void *);

// Just so we know it's OUR object.
#define PBRT_MAGIC 'PBRT'

struct __PBRuntime {
    UInt32 Magic;
    UInt32 RetainCount;
    UInt32 TypeID;
    PBRuntimeFinalize Finalize;
};

#endif /* PROJECTBUILDER_PRIVATE_PBRUNTIME_H */
