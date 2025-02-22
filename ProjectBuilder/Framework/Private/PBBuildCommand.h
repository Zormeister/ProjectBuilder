// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#ifndef PROJECTBUILDER_PBBUILDCOMMAND_H
#define PROJECTBUILDER_PBBUILDCOMMAND_H

#include <CoreFoundation/CoreFoundation.h>

#include <ProjectBuilder/PBEnvironment.h>
#include <ProjectBuilder/PBConstants.h>
#include <ProjectBuilder/PBConfig.h>

typedef struct _PBBuildCommand *PBBuildCommandRef;

CF_EXPORT PBBuildCommandRef PBBuildCommandCreateWithBuildSystem(PBBuildSystem system, PBEnvironmentRef env, CFArrayRef additionalArgs);

#endif /* PROJECTBUILDER_PBBUILDCOMMAND_H */
