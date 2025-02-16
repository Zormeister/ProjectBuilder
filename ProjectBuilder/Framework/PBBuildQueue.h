// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#ifndef PROJECTBUILDER_PBBUILDQUEUE_H
#define PROJECTBUILDER_PBBUILDQUEUE_H

#include <CoreFoundation/CoreFoundation.h>

#include <ProjectBuilder/PBProject.h>

typedef struct _PBBuildQueue *PBBuildQueueRef;

bool PBBuildQueueAddProject(PBBuildQueueRef queue, PBProjectRef project);

PBBuildQueueRef PBBuildQueueCreateWithProjects(CFArrayRef projectArray);

PBProjectRef PBBuildQueueGetNextProjectInQueue(PBBuildQueueRef buildQueue);

void PBBuildQueueEnqueue(PBProjectRef project);
void PBBuildQueueDequeue(PBProjectRef project);

#endif
