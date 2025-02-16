// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#include <iostream>
#include <string>

#define ENSURE_ARGS() \
    if (argc < i + 1) { printf("Bad Arguments - insufficient args."); abort(); }

const char *destintationRoot;

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
        } else if (s == "-d") {
            ENSURE_ARGS();
            destintationRoot = argv[i + 1];
            // If we have no destination root, just leave the binaries in /Library/Caches/com.Zormeister.ProjectBuilder/<Build UUID>/
        }
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
