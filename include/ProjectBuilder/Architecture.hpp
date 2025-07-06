// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#ifndef PROJECTBUILDER_ARCHITECTURE_HPP
#define PROJECTBUILDER_ARCHITECTURE_HPP

#include <map>
#include <string>
#include <ProjectBuilder/Base.hpp>

#if __has_include(<mach/machine.h>)
#include <mach/machine.h>
#else

typedef uint32_t cpu_type_t;
typedef uint32_t cpu_subtype_t;

#endif

namespace ProjectBuilder {

class Architecture {
    
public:
    Architecture();
    Architecture(cpu_type_t Arch);
    Architecture(cpu_type_t Arch, cpu_subtype_t SubArch);
    
    bool isArch(cpu_type_t Arch);
    
    cpu_type_t getArch();
    
private:
    cpu_type_t _arch;
    cpu_subtype_t _subarch;
};
    
}


#endif /* PROJECTBUILDER_ARCHITECTURE_HPP */
