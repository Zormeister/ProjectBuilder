// Copyright (C) 2024-2025 Zormeister, All rights reserved. Licensed under the BSD-3 Clause License.

#ifndef PROJECTBUILDER_PROJECTBUILDER_H
#define PROJECTBUILDER_PROJECTBUILDER_H

#ifdef __cplusplus
#define PB_EXPORT extern "C"
#else
#define PB_EXPORT extern
#endif

//! Project version number for ProjectBuilder.
PB_EXPORT double ProjectBuilderVersionNumber;

//! Project version string for ProjectBuilder.
PB_EXPORT const unsigned char ProjectBuilderVersionString[];

#endif
