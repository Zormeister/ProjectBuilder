// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#ifndef PROJECTBUILDER_PROJECT_HPP
#define PROJECTBUILDER_PROJECT_HPP

#include <map>
#include <ProjectBuilder/Base.hpp>
#include <ProjectBuilder/Architecture.hpp>
#include <cpplist/cpplist.hpp>

namespace ProjectBuilder {
    using namespace cpplist;

    class Project {
        public:
        Project(std::shared_ptr<cpplist::Dictionary> ProjectInfo);

        /* Build Environment related stuff */
        std::vector<Architecture> GetArchs();
        const std::string &GetName();
        const std::string &GetRealName();
        const std::string &GetSourcePath();
        const std::string &GetBuildSystem();

        /* Environment services */
        bool ModifyEnvrionment(const std::string &Name, const std::string &Value);
        void RemoveEnvironmentVariable(const std::string &VarName);
        
        bool Build();

        private:
        std::map<std::string, std::string> m_environmentVariables;
    };

}

#endif /* PROJECTBUILDER_PROJECT_HPP */
