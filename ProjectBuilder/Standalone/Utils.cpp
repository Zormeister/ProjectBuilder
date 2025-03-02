// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#include <stdio.h>

#include <sys/stat.h>
#include <CoreFoundation/CoreFoundation.h>

/* C */

bool DirectoryExists_C(const char *dirPath) {
    struct stat s;
    if (stat(dirPath, &s) == 0 && S_ISDIR(s.st_mode)) {
        return true;
    } else {
        return false;
    }
}

bool DirectoryExistsCF(CFStringRef cf) {
    struct stat s;
    if (stat(CFStringGetCStringPtr(cf, kCFStringEncodingASCII), &s) == 0 && S_ISDIR(s.st_mode)) {
        return true;
    } else {
        return false;
    }
}

void CreateDirectory_C(const char *path) {
    mkpath_np(path, 0755); // hopefully it expects the octal format???
}

/* C++ FS impl */

#include <filesystem>

bool DirectoryExists_CXX(const char *path) {
    std::filesystem::path fspath(path); /* ?? */
    /* im experimenting with C++ */
    if (std::filesystem::exists(fspath) && std::filesystem::is_directory(fspath)) {
        return true;
    } else {
        return false;
    }
}
