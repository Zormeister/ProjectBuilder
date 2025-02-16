// Copyright (C) 2024-2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#ifndef PROJECTBUILDER_PBBUILDER_H
#define PROJECTBUILDER_PBBUILDER_H

#include <PBManifest.h>
#include <PBBuildQueue.h>
#include <PBProject.h>

typedef struct _PBBuilder *PBBuilderRef;

enum PBBuilderError {
    BuildSystemFailed,
};

typedef void (*PBBuilderCompletionCallback)(void);
typedef void (*PBBuilderErrorCallback)(void);

enum PBBuilderState {
    CopyingSources,
    CopiedSources,
    BuildingSources,
    BuiltSources,
    InstallingBinaries,
    MovingToNextProject,
};

PBBuilderRef PBBuilderCreateBuildQueue(PBBuildQueueRef buildQueue);

#endif
