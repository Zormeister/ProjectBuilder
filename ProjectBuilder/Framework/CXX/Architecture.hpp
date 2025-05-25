// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#ifndef PROJECTBUILDER_ARCHITECTURE_HPP
#define PROJECTBUILDER_ARCHITECTURE_HPP

#include <map>
#include <string>
#if __APPLE__
#include <ProjectBuilder/Base.hpp>
#else
#include "Base.hpp"
#endif

namespace ProjectBuilder {

    enum {
        x86_64, /*  */
        i386,
        ARMv6,
        ARMv7,
        ARM64,
        ARM64_32,
    } typedef Arch;

    typedef enum {
        x86_64h = 1,
        ARMv7s = 1,
        ARMv7k = 2,
    } ArchVariant;

    typedef struct {
        Arch Arch;
        ArchVariant Variant;
    } Architecture;
}


#endif /* PROJECTBUILDER_ARCHITECTURE_HPP */
