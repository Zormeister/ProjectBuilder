// Copyright (c) 2026, Samuel Zormeister. All rights reserved. SPDX: BSD-3-Clause

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFString.h>
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
    //
    // This would also work on GNU Mach, I think.
    //
    // As if I'd ever use that.
    //
#if __APPLE__
    struct host_basic_info info;
    mach_msg_type_number_t info_cnt = sizeof(struct host_basic_info) / sizeof(integer_t);

    host_info(mach_host_self(), HOST_BASIC_INFO, (host_info_t)&info, &info_cnt);

    *type = info.cpu_type;
    *subType = info.cpu_subtype;
#else
    //
    // There isn't really a convenient way to get the current CPU architecture on glibc, or musl for that matter.
    //
    #if __x86_64__
        *type = kPBArchitectureCPUTypeX86_64;
        *subType = kPBArchitectureX86_64SubTypeAll;
    #elif __aarch64__
        *type = kPBArchitectureCPUTypeARM64;
        *subType = kPBArchitectureARM64SubTypeAll;
    #else
        PB_BUG_CRASH("Host Architecture is unaccounted for!");
    #endif
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
#if CF_RECLAIM_AVAILABLE
    NULL,                   // reclaim
#endif
#if CF_REFCOUNT_AVAILABLE
    NULL,                   // refcount
#endif
#if CF_REQUIRED_ALIGNMENT_AVAILABLE
    0,                      // requiredAlignment
#endif
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

struct __PBArchitecture __PBArchitectureX86_64H = {
    .archString = CFSTR("x86_64h"),
    .cpuType = kPBArchitectureCPUTypeX86_64,
    .cpuSubType = kPBArchitectureX86_64SubTypeHaswell,
};

const PBArchitectureRef kPBArchitectureX86_64H = &__PBArchitectureX86_64H;

struct __PBArchitecture __PBArchitectureARMV6 = {
    .archString = CFSTR("armv6"),
    .cpuType = kPBArchitectureCPUTypeARM,
    .cpuSubType = kPBArchitectureARMSubTypeV6,
};

const PBArchitectureRef kPBArchitectureARMV6 = &__PBArchitectureARMV6;

struct __PBArchitecture __PBArchitectureARMV7 = {
    .archString = CFSTR("armv7"),
    .cpuType = kPBArchitectureCPUTypeARM,
    .cpuSubType = kPBArchitectureARMSubTypeV7,
};

const PBArchitectureRef kPBArchitectureARMV7 = &__PBArchitectureARMV7;

struct __PBArchitecture __PBArchitectureARMV7S = {
    .archString = CFSTR("armv7s"),
    .cpuType = kPBArchitectureCPUTypeARM,
    .cpuSubType = kPBArchitectureARMSubTypeV7S,
};

const PBArchitectureRef kPBArchitectureARMV7S = &__PBArchitectureARMV7S;

struct __PBArchitecture __PBArchitectureARMV7K = {
    .archString = CFSTR("armv7k"),
    .cpuType = kPBArchitectureCPUTypeARM,
    .cpuSubType = kPBArchitectureARMSubTypeV7K,
};

const PBArchitectureRef kPBArchitectureARMV7K = &__PBArchitectureARMV7K;

struct __PBArchitecture __PBArchitectureARM64 = {
    .archString = CFSTR("arm64"),
    .cpuType = kPBArchitectureCPUTypeARM64,
    .cpuSubType = kPBArchitectureARM64SubTypeAll,
};

const PBArchitectureRef kPBArchitectureARM64 = &__PBArchitectureARM64;

struct __PBArchitecture __PBArchitectureARM64E = {
    .archString = CFSTR("arm64e"),
    .cpuType = kPBArchitectureCPUTypeARM64,
    .cpuSubType = kPBArchitectureARM64SubTypeARM64E,
};

const PBArchitectureRef kPBArchitectureARM64E = &__PBArchitectureARM64E;

void __PBArchitectureRegister(void)
{
    __PBArchitectureTypeID = _CFRuntimeRegisterClass(&__PBArchitectureClass);
    _CFRuntimeInitStaticInstance(&__PBArchitectureX86_64, __PBArchitectureTypeID);
    _CFRuntimeInitStaticInstance(&__PBArchitectureX86_64H, __PBArchitectureTypeID);
    _CFRuntimeInitStaticInstance(&__PBArchitectureARMV6, __PBArchitectureTypeID);
    _CFRuntimeInitStaticInstance(&__PBArchitectureARMV7, __PBArchitectureTypeID);
    _CFRuntimeInitStaticInstance(&__PBArchitectureARMV7S, __PBArchitectureTypeID);
    _CFRuntimeInitStaticInstance(&__PBArchitectureARMV7K, __PBArchitectureTypeID);
    _CFRuntimeInitStaticInstance(&__PBArchitectureARM64, __PBArchitectureTypeID);
    _CFRuntimeInitStaticInstance(&__PBArchitectureARM64E, __PBArchitectureTypeID);
}

CFTypeID PBArchitectureGetTypeID(void)
{
    if (__PBArchitectureTypeID == _kCFRuntimeNotATypeID) {
        __PBArchitectureRegister();
    }

    return __PBArchitectureTypeID;
}

PBArchitectureRef PBArchitectureGetFromHost(void)
{
    PBArchitectureCPUType type = 0;             // TODO: invalid value?
    PBArchitectureCPUSubType subType = 0;       // TODO: invalid value?

    __PBArchitectureGetHostArch(&type, &subType);

    //
    // Safety check.
    //
    (void)PBArchitectureGetTypeID();

    switch (type) {
        case kPBArchitectureCPUTypeX86_64:
            if (subType == kPBArchitectureX86_64SubTypeHaswell) {
                return kPBArchitectureX86_64H;
            } else {
                return kPBArchitectureX86_64;
            }
        case kPBArchitectureCPUTypeARM:
            switch (subType) {
                case kPBArchitectureARMSubTypeV6:
                    return kPBArchitectureARMV6;
                case kPBArchitectureARMSubTypeV7:
                    return kPBArchitectureARMV7;
                case kPBArchitectureARMSubTypeV7S:
                    return kPBArchitectureARMV7S;
                case kPBArchitectureARMSubTypeV7K:
                    return kPBArchitectureARMV7K;
            }
            return NULL;
        default:
            break;
    }

    return NULL;
}

CFStringRef PBArchitectureGetName(PBArchitectureRef arch)
{
    return arch->archString;
}

PBArchitectureCPUType PBArchitectureGetCPUType(PBArchitectureRef arch)
{
    return arch->cpuType;
}

PBArchitectureCPUSubType PBArchitectureGetCPUSubType(PBArchitectureRef arch)
{
    return arch->cpuSubType;
}
