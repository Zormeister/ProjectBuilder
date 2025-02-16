// Copyright (C) 2024-2025 Zormeister, All rights reserved. Licensed under the BSD-3 Clause License.

#pragma once
#include <CoreFoundation/CoreFoundation.h>

//! Project version number for ProjectBuilder.
CF_EXPORT double ProjectBuilderVersionNumber;

//! Project version string for ProjectBuilder.
CF_EXPORT const unsigned char ProjectBuilderVersionString[];

#include <ProjectBuilder/PBManifest.h>
#include <ProjectBuilder/PBProject.h>
#include <ProjectBuilder/PBBuilder.h>
#include <ProjectBuilder/PBBuildQueue.h>

CF_EXPORT void PBRelease(void *);
CF_EXPORT void PBRetain(void *);

CF_EXPORT UInt32 PBGetTypeID(void *);
