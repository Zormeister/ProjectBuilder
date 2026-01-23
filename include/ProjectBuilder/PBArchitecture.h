// Copyright (c) 2026, Samuel Zormeister. All rights reserved. SPDX: BSD-3-Clause

#ifndef __PROJECTBUILDER_PBARCHITECTURE__
#define __PROJECTBUILDER_PBARCHITECTURE__

#include <ProjectBuilder/PBBase.h>

CF_EXTERN_C_BEGIN

PB_DECLARE_CLASS(PBArchitecture);

//
// These should be aligned with MACH defintions.
//
typedef CF_ENUM(UInt32, PBArchitectureCPUType) {
    kPBArchitectureCPUTypeX86       = 0x7,
    kPBArchitectureCPUTypeX86_64    = 0x1000007,
    
    kPBArchitectureCPUTypeARM       = 12,
    kPBArchitectureCPUTypeARM64     = 0x100000C,
    kPBArchitectureCPUTypeARM64_32  = 0x200000C,
};

//
// random thought; but since ARM64_32 exists, could X32 be ported to Mach-O?
//

typedef CF_ENUM(UInt32, PBArchitectureCPUSubType) {
    kPBArchitectureX86_64SubTypeAll       = 0x3,
    kPBArchitectureX86_64SubTypeHaswell   = 0x8,
    
    kPBArchitectureARMSubTypeV6           = 0x6,
    kPBArchitectureARMSubTypeV7           = 0x9,
    kPBArchitectureARMSubTypeV7F          = 0xA,
    kPBArchitectureARMSubTypeV7S          = 0xB,
    kPBArchitectureARMSubTypeV7K          = 0xC,
    
    kPBArchitectureARM64SubTypeAll        = 0x0,
    kPBArchitectureARM64SubTypeV8         = 0x1,
    kPBArchitectureARM64SubTypeARM64E     = 0x2,
};

CFTypeID PBArchitectureGetTypeID(void);

//
// This will return one of the constants.
//
PBArchitectureRef PBArchitectureGetFromHost(void);

//
// This will return one of the constant PBArchitecture objects.
//
PBArchitectureRef PBArchitectureGetFromString(CFStringRef string);

//
// This list consists of architectures native to Xcode.
//
const PBArchitectureRef kPBArchitectureARM64;
const PBArchitectureRef kPBArchitectureARM64E;

const PBArchitectureRef kPBArchitectureARMV7;
const PBArchitectureRef kPBArchitectureARMV7S;
const PBArchitectureRef kPBArchitectureARMV7K;

const PBArchitectureRef kPBArchitectureX86_64;
const PBArchitectureRef kPBArchitectureX86_64H;

CF_EXTERN_C_END

#endif /* __PROJECTBUILDER_PBARCHITECTURE__ */
