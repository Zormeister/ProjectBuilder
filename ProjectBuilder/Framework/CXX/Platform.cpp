// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#include "Platform.hpp"
#include "CXXSupport/PropertyList.hpp"
#include <filesystem>
#include <memory>
#include <stdexcept>
#include <vector>
#include <fstream>

using namespace ProjectBuilder;

std::vector<Platform> Platform::GetAvailablePlatforms() {
    static const char *PLATFORM_SEARCH_PATHS[] = {
        "/Applications/Xcode.app/Contents/Developer/Platforms"
    };

    std::vector<Platform> platvec;
    for (int i = 0; i < sizeof(PLATFORM_SEARCH_PATHS) / sizeof(const char *); i++) {
        std::string path = PLATFORM_SEARCH_PATHS[i];
        if (std::filesystem::exists(path)) {
            for (const auto &entry : std::filesystem::directory_iterator(path)) {
                if (entry.is_directory()) { // .platform 'bundles' are just folders.
                    std::filesystem::path path = entry.path();
                    path += "/Info.plist";
                    auto size = std::filesystem::file_size(path);
                    std::vector<uint8_t> vec(size); // we don't want to accidentally spill over if we have a binary plist ngl

                    std::fstream stream;
                    stream.open(path);
                    // i assume im not trying to write any new data. i just want to parse it in memory.
                    stream.read((char *)vec.data(), size);

                    stream.close();

                    PropertyList::File file(vec);
                    platvec.push_back(Platform(file));
                }
            }
        }
    };

    return platvec;
};

Platform::Platform(PropertyList::File file) : m_platformInfoFile(file) {
    auto rn = m_platformInfoFile.GetRootNode();
    if (rn->GetNodeType() != PropertyList::Node::NodeType::Dictionary) {
        throw std::runtime_error("that isn't supposed to happen");
    }
    auto dict = std::dynamic_pointer_cast<PropertyList::Dictionary>(rn);
    if (dict->ContainsKey("FamilyName")) {
        // wip
    }
}