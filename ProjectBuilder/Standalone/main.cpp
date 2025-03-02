// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#include <CoreFoundation/CoreFoundation.h>
#include <ProjectBuilder/PBProject.h>

#include <sys/stat.h>
#include <sysdir.h>
#include <pwd.h>

#include <string>
#include <filesystem>

/* So much C++ code here, If I can find out how 2 do this in C++ I'll explore it. For now though... */

static bool DirectoryExists(const char *dirPath) {
    struct stat s;
    if (stat(dirPath, &s) == 0 && S_ISDIR(s.st_mode)) {
        return true;
    } else {
        return false;
    }
}

static bool DirectoryExistsCF(CFStringRef cf) {
    struct stat s;
    if (stat(CFStringGetCStringPtr(cf, kCFStringEncodingASCII), &s) == 0 && S_ISDIR(s.st_mode)) {
        return true;
    } else {
        return false;
    }
}

static void CreateDirectory(const char *path) {
    mkpath_np(path, 0755); // hopefully it expects the octal format???
}

#define ENSURE_ARGS() \
    if (argc < i + 1) { printf("Bad Arguments - insufficient args."); abort(); }

const char *plistPath;

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
        }
    }
}


#define DEFAULT_BUILDROOTS_DIRECTORY "/Library/BuildRoots"

int main(int argc, const char * argv[]) {
    /* This is me testing my shitcode. */
    struct passwd *pwd = getpwuid(getuid());
    size_t size = strlen("/Users/") + strlen(pwd->pw_name) + strlen(DEFAULT_BUILDROOTS_DIRECTORY);
    char *tmp = (char *)malloc(size);
    snprintf(tmp, size, "/Users/%s%s", pwd->pw_name, DEFAULT_BUILDROOTS_DIRECTORY);
    if (!DirectoryExists(tmp)) {
        CreateDirectory(tmp);
    }
    // thus we have created our buildroots directory. clap clap.
    // i need to test PBDiskImage smh
    free(tmp);
    return 0;
}
