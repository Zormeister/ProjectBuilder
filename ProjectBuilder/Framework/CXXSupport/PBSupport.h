// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#ifndef PROJECTBUILDER_SUPPORT_PBSUPPORT_H
#define PROJECTBUILDER_SUPPORT_PBSUPPORT_H

#ifdef __cplusplus
#define SUPPORT_EXPORT extern "C"
#else
#define SUPPORT_EXPORT extern
#endif

//! Project version number for PBSupport.
SUPPORT_EXPORT double PBSupportVersionNumber;

//! Project version string for PBSupport.
SUPPORT_EXPORT const unsigned char PBSupportVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <PBSupport/PublicHeader.h>

#endif
