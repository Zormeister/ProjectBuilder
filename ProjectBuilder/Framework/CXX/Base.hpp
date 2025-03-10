// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#ifndef PROJECTBUILDER_BASE_HPP
#define PROJECTBUILDER_BASE_HPP

/* 
 * Why write a C++ API?
 * Science isn't about why, it's about why not.
 */

#define PB_BEGIN_NS namespace ProjectBuilder {
#define PB_END_NS };

/* This might have the effect of creating logic inconsistencies. */
#if __APPLE__
#define BRIDGE_CF_API 1
#define TARGET_OS_MAC 1
#define TARGET_OS_LINUX 0
#else
#define BRIDGE_CF_API 0
#endif

/* backing up my notes & docs */

/* FORMERLY PBConstants.h: */

/*
 * Patches: An array of patches, read from the directory of the BuildInfo.plist file.
 *
 * Example configuration:
 *  - <DIRECTORY>/Patches
 *  - PB will read patches from here.
 * Otherwise, one can specifiy the directory in the Config section
 */

/*
 * External Repository: Signal to PB that we need to download a copy of the external repository.
 *
 * This uses the Type to determine how to get the sources we need.
 * Valid Values:
 *  - Git
 *
 * CommitSHA is the SHA hash of the commit to target
 * Tag is a string value of the tag to switch to.
 * URL points to the URL that the external repository is located at.
 */

/*
 * Archs: Specifies what architecture to build the project for, or, multiple architectures to build the project for.
 * If this isn't in a project entry, PB will use the host's native architecture.
 * Currently, PB will accept x86_64 and arm64 as valid targets.
 *
 * Valid Values:
 *  - x86_64
 *  - x86_64h - NOTE: Certain projects CANNOT use x86_64h - DO NOT use x86_64h for base system libraries. AT ALL.
 *  - arm64
 *  - arm
 *  - arm64_32
 */

/*
 * DOCS: This copies the directory specified in the Path key into the other project's directory
 * Example:
 * LLVM and TAPI,
 * TAPI needs to be under the LLVM source directory, so copy it INTO the LLVM source tree and build it later on using the command we want.
 * This is a STRING value.
 */

/*
 * BuildSystem: Tells ProjectBuilder what to expect.
 * Valid values as of ProjectBuilder V2:
 * - Makefile
 * - Xcode
 * - Script
 * - CMake
 *
 * Support can be later expanded in the future.
 * This is a STRING value.
 */

/*
 * SetXBSVariables: tells ProjectBuilder to set relevant XBS/DarwinBuild variables
 * such as but not limited to:
 *  - RC_ARCHS
 *  - RC_JASPER
 *  - RC_ProjectVersion
 *  - RC_ProjectSourceVersion
 *  - RC_ProjectName
 *  - RC_CFLAGS
 *  - RC_XBS
 *  - RC_Install_Prefix << Found in `iodbc`, I believe this should be set to `<PathToBuildRootRoot>/usr`
 */

/*
 * There are many other potential variables, I'm referencing the DarwinBuild plists so I can document them here.
 * Other Variables:
 *  - RC_NONARCH_CFLAGS: Non-architecture based C Flags I assume.
 *  - RC_OS: OS target?
 *  - RC_PRIVATE: private directory path? where else would they put the private directory?
 *  - RC_RELEASE: macOS named release. what does this really do? where is it used?
 *  - UNAME_RELEASE: uname release vers ig.
 *  - RC_TARGET_CONFIG: pretty much the same as XNU's PLATFORM variable in the makefile.
 */

/*
 * How the actual hell does DarwinBuild handle the cycle of dependencies?
 * Actually- I see how.
 * Certain projects are populated with dependencies.
 * Seems unreliable but OK.
 */

/*
 * Self-Reliant:
 *  - We use exclusively OUR headers as an SDK, use the Headers directory in the BuildRoot as our SDK.
 *  - There's a reason I put the SDKInit repository first in order in Darwin19.plist
 *  - There's also configurability for said self-reliant SDK. I'm beginning to regret my choice of rewriting PB.
 */

/*
 
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
 
 */

#endif
