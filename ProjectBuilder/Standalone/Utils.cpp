// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

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
