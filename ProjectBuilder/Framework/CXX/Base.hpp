// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#ifndef PROJECTBUILDER_BASE_HPP
#define PROJECTBUILDER_BASE_HPP

/* 
 * Why write a C++ API?
 * Science isn't about why, it's about why not.
 */

#define PB_BEGIN_NS namespace ProjectBuilder {
#define PB_END_NS };

/* CF API == C code. I'll have to update the Xcode project at some point so the C++ API and C API are segregated */
/* This also might have the effect of creating logic inconsistencies. */
#if __APPLE__
#define BRIDGE_CF_API 1
#else
#endif
#define BRIDGE_CF_API 0

#endif