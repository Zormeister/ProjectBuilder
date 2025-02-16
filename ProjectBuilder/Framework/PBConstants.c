// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#include "PBConstants.h"

const CFStringRef kPBManifestConfigKey = CFSTR("Config");
const CFStringRef kPBManifestProjectsKey = CFSTR("Projects");
const CFStringRef kPBManifestSubProjectsKey = CFSTR("SubProjects");
const CFStringRef kPBManifestPatchesKey = CFSTR("Patches");
const CFStringRef kPBManifestExternalRepositoryKey = CFSTR("ExternalRepository");
const CFStringRef kPBManifestExternalRepositoryTypeKey = CFSTR("Type");
const CFStringRef kPBManifestExternalRepositoryTagKey = CFSTR("Tag");
const CFStringRef kPBManifestExternalRepositoryCommitSHAKey = CFSTR("CommitSHA");
const CFStringRef kPBManifestExternalRepositoryURLKey = CFSTR("URL");

const CFStringRef kPBManifestBuildSystemKey = CFSTR("BuildSystem");

// do tell if I need to add more - I've been considering tampering with xmake for DarwinBoot, perhaps I need to add Meson and others.
const CFStringRef kPBManifestBuildSystemMakefile = CFSTR("Makefile");
const CFStringRef kPBManifestBuildSystemXcodeProject = CFSTR("Xcode");
const CFStringRef kPBManifestBuildSystemScript = CFSTR("Script");
const CFStringRef kPBManifestBuildSystemCMake = CFSTR("CMake");
