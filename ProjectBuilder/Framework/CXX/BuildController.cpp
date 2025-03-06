// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#include "BuildController.hpp"

#include <cstring>
#include <fstream>

#if TARGET_OS_LINUX
#include <linux/uuid.h>
#endif

using namespace ProjectBuilder;

BuildController::BuildController(const std::filesystem::path &BuildRootsPath, const std::filesystem::path &PropertyListPath) {
    std::ifstream plistStream(PropertyListPath);
#if TARGET_OS_LINUX
    uuid_t uuid;
    uuid_generate_random(uuid);
    memcpy(m_currentBuildUUID, uuid, sizeof(uuid_t));
#elif TARGET_OS_MAC
    CFUUIDRef cfUUID = CFUUIDCreate(kCFAllocatorDefault);
#endif
}