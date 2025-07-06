// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#include "BuildController.hpp"
#include <fstream>

using namespace ProjectBuilder;

BuildController::BuildController(const std::filesystem::path &BuildRootsPath, const std::filesystem::path &PropertyListPath) {
    std::ifstream plistStream(PropertyListPath);

    // perfect!
    uuid_generate_random(m_currentBuildUUID);

    /* Initialize PlugIns here. */
}
