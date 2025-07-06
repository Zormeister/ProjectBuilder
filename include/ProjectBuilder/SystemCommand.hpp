// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#ifndef PROJECTBUILDER_SYSTEMCOMMAND_HPP
#define PROJECTBUILDER_SYSTEMCOMMAND_HPP

#include <ProjectBuilder/Base.hpp>
#include <vector>

namespace ProjectBuilder {

    class SystemCommand {
        public:
        SystemCommand(std::string exec, std::vector<std::string> args);
        
        int Execute();
    };

}

#endif /* PROJECTBUILDER_SYSTEMCOMMAND_HPP */
