// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#ifndef PROJECTBUILDER_BUILDCONTROLLER_HPP
#define PROJECTBUILDER_BUILDCONTROLLER_HPP

#if __APPLE__
#include <ProjectBuilder/Base.hpp>
#else
#include "Base.hpp"
#endif

#include <filesystem>
#include <uuid/uuid.h>

namespace ProjectBuilder {

    class BuildController {

        public:
        /* Ripped from PBBuildController.h */
        enum struct NotificationReason {
            ProjectStatusChanged,
            FinishedBuildingAllProjects,
        };

        typedef void (*Notification)(BuildController::NotificationReason Reason, void *Data);

        BuildController(const std::filesystem::path &BuildRootsPath, const std::filesystem::path &PropertyListPath);

        const std::filesystem::path &GetBuildRootsPath(); /* I believe we need this for DI and others. */

        void StartBuildingProjects(); /* Equivalent to PBBuildControllerBegin() */

        void SetNotifier(Notification notifier);

        private:
        std::filesystem::path m_buildRootsPath; /* Derived from what's passed to the constructor */
        std::filesystem::path m_propertyListPath; /* Derived from what's passed to the constructor */

        uuid_t m_currentBuildUUID;
        Notification m_notifier;
};

}

#endif
