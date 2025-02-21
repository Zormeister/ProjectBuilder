// Copyright (C) 2024-2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#ifndef PROJECTBUILDER_PBMANIFEST_H
#define PROJECTBUILDER_PBMANIFEST_H

#include <CoreFoundation/CoreFoundation.h>

#include <ProjectBuilder/PBProject.h>

typedef struct _PBManifest *PBManifestRef;

CF_EXPORT PBManifestRef PBManifestCreateWithPropertyList(CFPropertyListRef propertyList);

CF_EXPORT CFArrayRef PBManifestGetProjects(PBManifestRef manifest);

CF_EXPORT CFBooleanRef PBManifestGetAbortOnError(PBManifestRef manifest);

CF_EXPORT PBProjectRef PBManifestGetProjectByName(CFStringRef name);

#endif
