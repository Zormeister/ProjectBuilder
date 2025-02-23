// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#ifndef PROJECTBUILDER_PBPROJECTINFO_H
#define PROJECTBUILDER_PBPROJECTINFO_H

#include <CoreFoundation/CoreFoundation.h>

typedef struct _PBProjectInfo *PBProjectInfoRef;

CF_EXPORT CFStringRef PBProjectInfoGetName(PBProjectInfoRef projInfo);

CF_EXPORT CFStringRef PBProjectInfoGetVersion(PBProjectInfoRef projInfo);


#endif /* PROJECTBUILDER_PBPROJECTINFO_H */
