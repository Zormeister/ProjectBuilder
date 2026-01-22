// Copyright (c) 2026, Samuel Zormeister. All rights reserved. SPDX: BSD-3-Clause

#include <ProjectBuilder/PBArchitecture.h>
#include <CoreFoundation/CFRuntime.h>

struct __PBArchitecture {
    struct __CFRuntimeBase cfBase;
    
    CFStringRef archString;
    
    PBArchitectureCPUType cpuType;
    PBArchitectureCPUSubType cpuSubType;
};

static CFTypeID __PBArchitectureTypeID = _kCFRuntimeNotATypeID;

static Boolean __PBArchitectureEqual(CFTypeRef type1, CFTypeRef type2)
{
    if (CFGetTypeID(type1) == PBArchitectureGetTypeID() &&
        CFGetTypeID(type2) == PBArchitectureGetTypeID())
    {
        PBArchitectureRef Arch1 = (PBArchitectureRef)type1;
        PBArchitectureRef Arch2 = (PBArchitectureRef)type2;
        
        if (CFEqual(Arch1->archString, Arch2->archString)) {
            return true;
        }
    }
    
    return false;
}

static struct __CFRuntimeClass __PBArchitectureClass = {
    0,
    "PBArchitecture",
    NULL,                   // init
    NULL,                   // copy
    NULL,                   // finalize
    &__PBArchitectureEqual, // equal
    NULL,                   // hash
    NULL,                   // copyFormattingDesc
    NULL,                   // copyDebugDesc
    NULL,                   // reclaim
    NULL,                   // refcount
    0,                      // requiredAlignment
};

//
// Static architecture definitions.
//
struct __PBArchitecture __PBArchitectureX86_64 = {
    .archString = CFSTR("x86_64"),
    .cpuType = kPBArchitectureCPUTypeX86_64,
};

const PBArchitectureRef kPBArchitectureX86_64 = &__PBArchitectureX86_64;

CFTypeID PBArchitectureGetTypeID(void)
{
    if (__PBArchitectureTypeID == _kCFRuntimeNotATypeID) {
        __PBArchitectureTypeID = _CFRuntimeRegisterClass(&__PBArchitectureClass);
        _CFRuntimeInitStaticInstance(&__PBArchitectureX86_64, __PBArchitectureTypeID);
    }
    
    return __PBArchitectureTypeID;
}
