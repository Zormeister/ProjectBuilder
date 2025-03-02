// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#ifndef PROJECTBUILDER_PBPROJECTINFO_H
#define PROJECTBUILDER_PBPROJECTINFO_H

#include <CoreFoundation/CoreFoundation.h>

typedef struct _PBProjectInfo *PBProjectInfoRef;

CF_EXPORT CFStringRef PBProjectInfoGetName(PBProjectInfoRef projInfo);

/* This is because variants. I hate this. */
CF_EXPORT CFStringRef PBProjectInfoGetInternalName(PBProjectInfoRef projInfo);

CF_EXPORT CFStringRef PBProjectInfoGetVersion(PBProjectInfoRef projInfo);

/* SRCROOT, DSTROOT, OBJROOT */
CF_EXPORT CFStringRef PBProjectInfoGetSourceRoot(PBProjectInfoRef projInfo);
CF_EXPORT CFStringRef PBProjectInfoGetDestinationRoot(PBProjectInfoRef projInfo);
CF_EXPORT CFStringRef PBProjectInfoGetObjectRoot(PBProjectInfoRef projInfo);

#endif /* PROJECTBUILDER_PBPROJECTINFO_H */
