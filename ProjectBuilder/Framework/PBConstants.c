// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#include "PBConstants.h"

const CFStringRef kPBManifestConfigKey = CFSTR("Config");
const CFStringRef kPBManifestProjectsKey = CFSTR("Projects");
const CFStringRef kPBManifestSubProjectsKey = CFSTR("SubProjects");
const CFStringRef kPBManifestPatchesKey = CFSTR("Patches");
const CFStringRef kPBExternalRepositoryKey = CFSTR("ExternalRepository");
const CFStringRef kPBExternalRepositoryTypeKey = CFSTR("Type");
const CFStringRef kPBExternalRepositoryTagKey = CFSTR("Tag");
const CFStringRef kPBExternalRepositoryCommitSHAKey = CFSTR("CommitHash");
const CFStringRef kPBExternalRepositoryURLKey = CFSTR("URL");

const CFStringRef kPBManifestBuildSystemKey = CFSTR("BuildSystem");

// do tell if I need to add more - I've been considering tampering with xmake for DarwinBoot, perhaps I need to add Meson and others.
const CFStringRef kPBManifestBuildSystemMakefile = CFSTR("Makefile");
const CFStringRef kPBManifestBuildSystemXcodeProject = CFSTR("Xcode");
const CFStringRef kPBManifestBuildSystemScript = CFSTR("Script");
const CFStringRef kPBManifestBuildSystemCMake = CFSTR("CMake");

const CFStringRef kPBDiskImageVolumeNameKey = CFSTR("VolumeName");
const CFStringRef kPBDiskImageDiskSizeKey = CFSTR("Size");
const CFStringRef kPBDiskImageDiskTypeKey = CFSTR("Type");
const CFStringRef kPBDiskImageDiskLayoutKey = CFSTR("Layout");
const CFStringRef kPBDiskImageFileSystemKey = CFSTR("FileSystem");
