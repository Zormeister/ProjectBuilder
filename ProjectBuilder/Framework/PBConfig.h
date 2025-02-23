// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#ifndef PROJECTBUILDER_PBCONFIG_H
#define PROJECTBUILDER_PBCONFIG_H

#include <CoreFoundation/CoreFoundation.h>

typedef struct _PBConfiguration *PBConfigurationRef;

/*
 * Self-Reliant:
 *  - We use exclusively OUR headers as an SDK, use the Headers directory in the BuildRoot as our SDK.
 *  - There's a reason I put the SDKInit repository first in order in Darwin19.plist
 */
CF_EXPORT CFBooleanRef PBConfigurationIsSelfReliant(PBConfigurationRef cfg);

/*
 * Sets XBS Variables:
 *  - explained in PBConstants
 */
CF_EXPORT CFBooleanRef PBConfigurationSetsXBSVariables(PBConfigurationRef cfg);

#endif /* PROJECTBUILDER_PBCONFIG_H */
