// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#include <sys/stat.h>
#include <pwd.h>

#include <string>
#include <cstring>
#include <filesystem>

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
        }
    }
}


#define DEFAULT_BUILDROOTS_DIRECTORY "/Library/BuildRoots"

int main(int argc, const char * argv[]) {
    /* This is me testing my shitcode. */
    struct passwd *pwd = getpwuid(getuid());
    return 0;
}
