// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#include "PropertyList.hpp"
#include "libxml/parser.h"
#include "libxml/xmlstring.h"
#include <memory>

using namespace PBSupport::PropertyList;

Dictionary::Dictionary(xmlNodePtr XMLNode) : Node() {
    xmlNodePtr child;
    const char *key = nullptr;
    for (child = XMLNode->children; child != nullptr; child = child->next) {
        if (child->type == XML_ELEMENT_NODE) {
            if (xmlStrcmp(child->name, (xmlChar *)"key") == 0) {
                key = (const char *)xmlNodeGetContent(child);
            } else {
                if (key) {
                    switch (GetNodeTypeForXMLNode(child)) {
                        case NodeType::Array:
                            m_map.insert_or_assign(key, std::make_shared<Array>(child));
                            break;
                        case NodeType::Boolean:
                            m_map.insert_or_assign(key, std::make_shared<Boolean>(child));
                            break;
                        case NodeType::String:
                            m_map.insert_or_assign(key, std::make_shared<String>(child));
                            break;
                        case NodeType::Data:
                            m_map.insert_or_assign(key, std::make_shared<Data>(child));
                            break;
                        case NodeType::Date:
                            m_map.insert_or_assign(key, std::make_shared<Date>(child));
                            break;
                        case NodeType::Dictionary:
                            m_map.insert_or_assign(key, std::make_shared<Dictionary>(child));
                            break;
                        case NodeType::Integer:
                            m_map.insert_or_assign(key, std::make_shared<Integer>(child));
                            break;
                        default:
                            break;
                    }
                } else {
                    continue;
                }
            }
        }
    }
}

bool Dictionary::ContainsKey(const std::string &Key) {
    if (m_map.count(Key) == 0) {
        return false;
    } else {
        return true;
    }
}
