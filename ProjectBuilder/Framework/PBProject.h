// Copyright (C) 2024-2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#ifndef PROJECTBUILDER_PBPROJECT_H
#define PROJECTBUILDER_PBPROJECT_H

#include <CoreFoundation/CoreFoundation.h>

typedef struct _PBProject *PBProjectRef;

/* NEW: Sub-Projects. Added in the overhaul */
CF_EXPORT CFArrayRef PBProjectGetSubProjects(PBProjectRef project);

/* NEW: Patch applier. Added in the overhaul */
CF_EXPORT CFArrayRef PBProjectGetPatches(PBProjectRef project);

CF_EXPORT CFStringRef PBProjectGetName(PBProjectRef project);

CF_EXPORT CFBooleanRef PBProjectIsExternalRepo(PBProjectRef project);

CF_EXPORT CFBooleanRef PBProjectBuildProject(PBProjectRef project);

CF_EXPORT CFBooleanRef PBProjectIsBuilt(PBProjectRef project);

CF_EXPORT CFArrayRef PBProjectGetDependencies(PBProjectRef project);

#endif
