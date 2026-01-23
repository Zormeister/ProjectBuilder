// Copyright (c) 2026, Samuel Zormeister. All rights reserved. SPDX: BSD-3-Clause

#if __APPLE__
#include <mach/mach.h>
#include <mach/mach_host.h>
#endif

#include <ProjectBuilder/PBArchitecture.h>
#include <CoreFoundation/CFRuntime.h>

struct __PBArchitecture {
    struct __CFRuntimeBase cfBase;
    
    CFStringRef archString;
    
    PBArchitectureCPUType cpuType;
    PBArchitectureCPUSubType cpuSubType;
};

void __PBArchitectureGetHostArch(PBArchitectureCPUType *type, PBArchitectureCPUSubType *subType)
{
#if __APPLE__
    struct host_basic_info info;
    mach_msg_type_number_t info_cnt = sizeof(struct host_basic_info) / sizeof(integer_t);

    host_info(mach_host_self(), HOST_BASIC_INFO, (host_info_t)&info, &info_cnt);
    
    *type = info.cpu_type;
    *subType = info.cpu_subtype;
#endif // __APPLE__
}

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
    .cpuSubType = kPBArchitectureX86_64SubTypeAll,
};

const PBArchitectureRef kPBArchitectureX86_64 = &__PBArchitectureX86_64;

//
// Static architecture definitions.
//
struct __PBArchitecture __PBArchitectureX86_64H = {
    .archString = CFSTR("x86_64h"),
    .cpuType = kPBArchitectureCPUTypeX86_64,
    .cpuSubType = kPBArchitectureX86_64SubTypeHaswell,
};

const PBArchitectureRef kPBArchitectureX86_64H = &__PBArchitectureX86_64H;

void __PBArchitectureRegister(void)
{
    __PBArchitectureTypeID = _CFRuntimeRegisterClass(&__PBArchitectureClass);
    _CFRuntimeInitStaticInstance(&__PBArchitectureX86_64, __PBArchitectureTypeID);
}

CFTypeID PBArchitectureGetTypeID(void)
{
    if (__PBArchitectureTypeID == _kCFRuntimeNotATypeID) {
        __PBArchitectureTypeID = _CFRuntimeRegisterClass(&__PBArchitectureClass);
        _CFRuntimeInitStaticInstance(&__PBArchitectureX86_64, __PBArchitectureTypeID);
    }
    
    return __PBArchitectureTypeID;
}

PBArchitectureRef PBArchitectureGetFromHost(void)
{
    PBArchitectureCPUType type = 0;             // TODO: invalid value?
    PBArchitectureCPUSubType subType = 0;       // TODO: invalid value?
    
    __PBArchitectureGetHostArch(&type, &subType);
    
    switch (type) {
        case kPBArchitectureCPUTypeX86_64:
            if (subType == kPBArchitectureX86_64SubTypeHaswell) {
                return kPBArchitectureX86_64H;
            } else {
                return kPBArchitectureX86_64;
            }
        default:
            break;
    }
    
    return NULL;
}
