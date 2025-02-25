// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#ifndef PROJECTBUILDER_PBCONSTANTS_H
#define PROJECTBUILDER_PBCONSTANTS_H

#include <CoreFoundation/CoreFoundation.h>

CF_EXPORT const CFStringRef kPBManifestConfigKey;
CF_EXPORT const CFStringRef kPBManifestProjectsKey;
CF_EXPORT const CFStringRef kPBManifestSubProjectsKey;

/*
 * Patches: An array of patches, read from the directory of the BuildInfo.plist file.
 *
 * Example configuration:
 *  - <DIRECTORY>/Patches
 *  - PB will read patches from here.
 * Otherwise, one can specifiy the directory in the Config section
 */
CF_EXPORT const CFStringRef kPBManifestPatchesKey;
CF_EXPORT const CFStringRef kPBManifestPatchDirectoryKey;

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
CF_EXPORT const CFStringRef kPBExternalRepositoryKey;
CF_EXPORT const CFStringRef kPBExternalRepositoryTypeKey;
CF_EXPORT const CFStringRef kPBExternalRepositoryTagKey;
CF_EXPORT const CFStringRef kPBExternalRepositoryBranchKey;
CF_EXPORT const CFStringRef kPBExternalRepositoryCommitSHAKey;

CF_EXPORT const CFStringRef kPBEnvironmentVariablesKey;

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
CF_EXPORT const CFStringRef kPBManifestArchsKey;

/*
 * DOCS: This copies the directory specified in the Path key into the other project's directory
 * Example:
 * LLVM and TAPI,
 * TAPI needs to be under the LLVM source directory, so copy it INTO the LLVM source tree and build it later on using the command we want.
 * This is a STRING value.
 */
CF_EXPORT const CFStringRef kPBManifestEmbedIntoProjectKey;

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

CF_EXPORT const CFStringRef kPBManifestBuildSystemKey;

CF_EXPORT const CFStringRef kPBManifestBuildSystemMakefile;
CF_EXPORT const CFStringRef kPBManifestBuildSystemXcodeProject;
CF_EXPORT const CFStringRef kPBManifestBuildSystemScript;
CF_EXPORT const CFStringRef kPBManifestBuildSystemCMake;

typedef CF_ENUM(CFIndex, PBBuildSystem) {
    Unknown,
    Xcode,
    Makefile,
    Script,
    CMake,
};

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

CF_EXPORT const CFStringRef kPBSetXBSVariablesKey;


#pragma mark Disk Image Settings Keys

CF_EXPORT const CFStringRef kPBDiskImageVolumeNameKey;
CF_EXPORT const CFStringRef kPBDiskImageDiskSizeKey;
CF_EXPORT const CFStringRef kPBDiskImageDiskTypeKey;
CF_EXPORT const CFStringRef kPBDiskImageDiskLayoutKey;
CF_EXPORT const CFStringRef kPBDiskImageFileSystemKey;


#endif /* PROJECTBUILDER_PBCONSTANTS_H */
