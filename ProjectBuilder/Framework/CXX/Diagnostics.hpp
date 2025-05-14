// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#ifndef PROJECTBUILDER_DIAGNOSTICS_HPP
#define PROJECTBUILDER_DIAGNOSTICS_HPP

#if __APPLE__
#include <ProjectBuilder/Base.hpp>
#else
#include "Base.hpp"
#endif

#include <filesystem>
#include <uuid/uuid.h>

namespace ProjectBuilder {


class Diagnostics {
    public:
    Diagnostics(const std::filesystem::path &DiagnosticFilePath);
    
    
};


}

#endif
