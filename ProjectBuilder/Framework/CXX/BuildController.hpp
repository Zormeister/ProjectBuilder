// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#ifndef PROJECTBUILDER_BUILDCONTROLLER_HPP
#define PROJECTBUILDER_BUILDCONTROLLER_HPP

#if __APPLE__
#include <ProjectBuilder/Base.hpp>
#else
#include "Base.hpp"
#endif

#include <filesystem>

PB_BEGIN_NS

class BuildController {

    /* Ripped from PBBuildController.h */
    enum struct NotificationReason {
        ProjectStatusChanged,
        DiskImageCheckpoint,
        FinishedBuildingAllProjects,
    };

    struct DiskImageCheckpointData {
        /* TBD: I need to write DiskImage CXX API edition */
    };

    typedef void (*Notification)(BuildController::NotificationReason Reason, void *Data);

    BuildController(const std::filesystem::path &BuildRootsPath, const std::filesystem::path &PropertyListPath);

    std::filesystem::path GetBuildRootsPath(); /* I believe we need this for DI and others. */

    void StartBuildingProjects(); /* Equivalent to PBBuildControllerBegin() */

    private:
    std::filesystem::path m_buildRootsPath; /* Derived from what's passed to the constructor */
    std::filesystem::path m_propertyListPath; /* Derived from what's passed to the constructor */
};

PB_END_NS

#endif
