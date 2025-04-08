// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#include <sys/stat.h>
#include <pwd.h>

#include <string>
#include <cstring>
#include <filesystem>
#include <iostream>
#include "../Framework/CXX/Platform.hpp"

#if TARGET_OS_LINUX
#include <unistd.h>
#endif

/* So much C++ code here, If I can find out how 2 do this in C++ I'll explore it. For now though... */

#define ENSURE_ARGS() \
    if (argc < i + 1) { printf("Bad Arguments - insufficient args."); abort(); }

const char *plistPath;

std::string gBuildRootsPath;

enum InternalAction {
    Usage,
    Build,
    ListPlatforms,
};

InternalAction gCurrentAction = InternalAction::Usage;

void parse_args(int argc, const char *argv[]) {
    for (int i = 0; i <= argc; i++) {
        std::string s = argv[i];
        if (s == "build") {
            gCurrentAction = InternalAction::Build;
        } else if (s == "-p") {
            ENSURE_ARGS();
            plistPath = argv[i + 1];
            // If we have no destination root, just leave the binaries in /Library/Caches/com.Zormeister.ProjectBuilder/<Build UUID>/
        } else if (s == "-buildrootpath") {
            gBuildRootsPath = argv[i + 1];
        } else if (s == "--list-platforms") {
            gCurrentAction = InternalAction::ListPlatforms;
        }
    }
}


#define DEFAULT_BUILDROOTS_DIRECTORY "/Library/BuildRoots"

int main(int argc, const char * argv[]) {
    switch (gCurrentAction) {
        case ListPlatforms: {
            auto vec = ProjectBuilder::Platform::GetAvailablePlatforms();
            for (auto plat = vec.begin(); plat != vec.end(); ++plat) {
                std::cout << "Platform : " << plat->GetName() << std::endl;
            }
        };

        default:
        break;
    }
    return 0;
}
