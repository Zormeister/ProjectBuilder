// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#ifndef PROJECTBUILDER_SUPPORT_BASE_HPP
#define PROJECTBUILDER_SUPPORT_BASE_HPP

/* 
 * Suport framework?
 * me when no modern plist c++ library
 * i'll interface with libxml2 for ease of use...
 */

#define SUPPORT_BEGIN_NS namespace PBSupport {
#define SUPPORT_END_NS };

/* CF API == C code. I'll have to update the Xcode project at some point so the C++ API and C API are segregated */
/* This also might have the effect of creating logic inconsistencies. */
#if __APPLE__
#define BRIDGE_CF_API 1
#else
#define BRIDGE_CF_API 0
#endif

#endif