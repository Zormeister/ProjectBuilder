// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#include "../Framework/CXXSupport/PropertyList.hpp"
#include <cstdlib>
#include <stdexcept>
#include <filesystem>
#include <fstream>
#include <vector>

using namespace PBSupport;

const char *filePath;

char *plistMem;

void parse_args(int argc, const char *argv[]) {
    for (int i = 0; i < argc; i++) {
        std::string str = argv[i];
        if (str == "-p") {
            if ((i + 1) < argc) {
                filePath = argv[i + 1];
            } else {
                throw std::invalid_argument("no path for option -p");
            }
        }
    }
}

int main(int argc, const char *argv[]) {
    parse_args(argc, argv);
    if (filePath) {
        auto size = std::filesystem::file_size(filePath);
        std::vector<uint8_t> vec(size); // we don't want to accidentally spill over if we have a binary plist ngl

        std::fstream stream;
        stream.open(filePath);
        // i assume im not trying to write any new data. i just want to parse it in memory.
        stream.read((char *)vec.data(), size);

        stream.close();

        PropertyList::File file(vec);
    }
    return 0;
}