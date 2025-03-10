// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#include "BuildController.hpp"

#include <cstring>
#include <fstream>

#if TARGET_OS_LINUX
// This is needed on my system???
#include <linux/uuid.h>
#endif

using namespace ProjectBuilder;

BuildController::BuildController(const std::filesystem::path &BuildRootsPath, const std::filesystem::path &PropertyListPath) {
    std::ifstream plistStream(PropertyListPath);

    // perfect!
    uuid_generate_random(m_currentBuildUUID);
}
