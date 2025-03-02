// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#ifndef PROJECTBUILDER_PBBUILDCONTROLLER_H
#define PROJECTBUILDER_PBBUILDCONTROLLER_H

#include <ProjectBuilder/PBProject.h>

/* UNDER CONSTRUCTION!!! */

/*
 * Build Controller:
 * - THE object that does everything
 */
typedef struct _PBBuildController *PBBuildControllerRef;

/* Sends diagnostic messages */
typedef CF_ENUM(CFIndex, PBBuildControllerNotification) {
    FinishedProjectBuild, // Arguments supplied
    ProjectBuildFailed,
    DiskImageCreated,
    DiskImageMounted,
    FinishedBuildingAllProjects,
};

struct {
    CFStringRef project;
} typedef PBBCFinishedProjectBuildData;

typedef void (*PBBCNotification)(PBBuildControllerNotification notif, void *arg);

CF_EXPORT PBBuildControllerRef PBBuildControllerCreate(CFDictionaryRef dataRoot, CFURLRef buildRootDirectory);

CF_EXPORT void PBBuildControllerBegin(PBBuildControllerRef buildController);

CF_EXPORT void PBBuildControllerRegisterNotificationHandler(PBBuildControllerRef buildController, PBBCNotification notifHandler);

#endif /* PROJECTBUILDER_PBBUILDCONTROLLER_H */
