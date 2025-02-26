// Copyright (C) 2024-2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

/* the sole survivor of the late 2024 concepts */

#ifndef PROJECTBUILDER_PBPROJECT_H
#define PROJECTBUILDER_PBPROJECT_H

#include <CoreFoundation/CoreFoundation.h>

typedef struct _PBProject *PBProjectRef;

typedef CF_ENUM(CFIndex, PBProjectState) {
    Initialized,
    CopyingSources,
    CloningExternalRepo,
    BuildingProject,
    FinishedBuildingProject,
    DeployingBinaries, // Though- if we always run Xcode's install target will we ever have this set?
};

typedef void (*PBProjectStateUpdateNotification)(void *tgt, PBProjectState state);

/* TBD: Eliminate 'Sub Projects' entirely- the BC should see them as normal projects. */
CF_EXPORT CFArrayRef PBProjectGetSubProjects(PBProjectRef project);

CF_EXPORT CFArrayRef PBProjectGetPatches(PBProjectRef project);

CF_EXPORT CFStringRef PBProjectGetName(PBProjectRef project);

CF_EXPORT CFBooleanRef PBProjectIsExternalRepo(PBProjectRef project);

CF_EXPORT CFBooleanRef PBProjectBuildProject(PBProjectRef project);

CF_EXPORT CFBooleanRef PBProjectIsBuilt(PBProjectRef project);

CF_EXPORT CFArrayRef PBProjectGetDependencies(PBProjectRef project);

#endif
