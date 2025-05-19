// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#ifndef PROJECTBUILDER_PROJECT_HPP
#define PROJECTBUILDER_PROJECT_HPP

#include <map>
#if __APPLE__
#include <ProjectBuilder/Base.hpp>
#else
#include "Base.hpp"
#endif

namespace ProjectBuilder {

    class Project {
        /* Build Environment related stuff */
        const std::string &GetArch();
        const std::string &GetName();
        const std::string &GetRealName();
        const std::string &GetSourcePath();
        const std::string &GetBuildSystem();

        /*  */
        bool ModifyEnvrionment(const std::string &Name, const std::string &Value);
        void RemoveEnvironmentVariable(const std::string &VarName);

        private:
        std::map<std::string, std::string> m_environmentVariables;
    };

}

#endif /* PROJECTBUILDER_PROJECT_HPP */
