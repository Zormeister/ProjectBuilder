// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#include "../Framework/CXXSupport/PropertyList.hpp"
#include <cstdlib>
#include <iostream>
#include <memory>
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

void dump_plist_node(std::shared_ptr<PropertyList::Node> n) {
    switch (n->GetNodeType()) {
        case PropertyList::Node::NodeType::Array: {
            std::shared_ptr<PropertyList::Array> arrnode = std::dynamic_pointer_cast<PropertyList::Array>(n);
            std::cout << "Node : Array\n";
            for (int i = 0; i < arrnode->GetSize(); i++) {
                dump_plist_node(arrnode->GetNodeAtIndex(i));
            }
            break;
        }
        case PropertyList::Node::NodeType::Boolean: {
            std::shared_ptr<PropertyList::Boolean> boolnode = std::dynamic_pointer_cast<PropertyList::Boolean>(n);
            std::cout << "Node : Boolean : " << (boolnode->GetValue() ? "True" : "False") << "\n";
            break;
        }
        case PropertyList::Node::NodeType::Data: {
            
        }
        case PropertyList::Node::NodeType::Date:
        case PropertyList::Node::NodeType::Dictionary:
        case PropertyList::Node::NodeType::Integer:
        case PropertyList::Node::NodeType::String:
        case PropertyList::Node::NodeType::Unknown:
          break;
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
        auto rn = file.GetRootNode();
    }
    return 0;
}