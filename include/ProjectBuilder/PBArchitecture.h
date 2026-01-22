// Copyright (c) 2026, Samuel Zormeister. All rights reserved. SPDX: BSD-3-Clause

#ifndef __PROJECTBUILDER_PBARCHITECTURE__
#define __PROJECTBUILDER_PBARCHITECTURE__

#include <ProjectBuilder/PBBase.h>

PB_DECLARE_CLASS(PBArchitecture);

//
// These should be aligned with MACH defintions.
//
typedef CF_ENUM(UInt32, PBArchitectureCPUType) {
    kPBArchitectureCPUTypeX86       = 0x7,
    kPBArchitectureCPUTypeX86_64    = 0x10000007,
};

typedef CF_ENUM(UInt32, PBArchitectureCPUSubType) {
    kPBArchitectureX86_64SubTypeAll       = 0x3,
    kPBArchitectureX86_64SubTypeHaswell   = 0x8,
};

PB_EXPORT CFTypeID PBArchitectureGetTypeID(void);

PB_EXPORT PBArchitectureRef PBArchitectureCreateFromHostArch(CFAllocatorRef allocator);

PB_EXPORT PBArchitectureRef PBArchitectureCreateWithString(CFAllocatorRef allocator, CFStringRef string);

#endif /* __PROJECTBUILDER_PBARCHITECTURE__ */
