// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#ifndef PROJECTBUILDER_PBENVIRONMENT_H
#define PROJECTBUILDER_PBENVIRONMENT_H

#include <CoreFoundation/CoreFoundation.h>

#include <ProjectBuilder/PBProject.h>

/*
 * Environment
 *
 * BuildRoot: root of build
 */

typedef struct _PBEnvironment *PBEnvironmentRef;

CF_EXPORT CFStringRef PBEnvironmentGetBuildRootPath(PBEnvironmentRef env);

CF_EXPORT CFDictionaryRef PBEnvironmentGetShellEnvironment(PBEnvironmentRef env);

CF_EXPORT CFDictionaryRef PBEnvironmentAppendShellEnvironment(PBEnvironmentRef env, CFStringRef name, CFStringRef stringValue);

CF_EXPORT CFBooleanRef PBEnvironmentApplyEnvironmentVariables(PBEnvironmentRef env);

CF_EXPORT CFBooleanRef PBEnvironmentUpdateVariables(PBEnvironmentRef env, PBProjectRef project);

CF_EXPORT CFUUIDRef PBEnvironmentGetBuildUUID(PBEnvironmentRef env);

CF_EXPORT CFStringRef PBEnvironmentGetSDK(PBEnvironmentRef env);

struct {
    CFDictionaryRef shellArgs;
    CFStringRef buildRootDirectory; // /Library/BuildRoots/<UUID>
    CFStringRef sdkRoot; /* SDK, canonical name, so `macosx.internal` or macosx.internal.host */
    CFBooleanRef setsXBSVariables; /* see PBConstants.h for details */
    CFBooleanRef selfReliant;
} typedef PBEnvironmentArgs;

CF_EXPORT PBEnvironmentRef PBEnvironmentCreateWithArgs(PBEnvironmentArgs *args);

// We can actually also just set SDKROOT, afaik.
CF_EXPORT CFBooleanRef PBEnvironmentSetupWorkingDirectories(PBEnvironmentRef env);

#endif /* PROJECTBUILDER_PBENVIRONMENT_H */
