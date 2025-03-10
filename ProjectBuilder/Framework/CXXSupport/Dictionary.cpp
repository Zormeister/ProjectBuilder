// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#include "PropertyList.hpp"
#include "libxml/parser.h"
#include "libxml/xmlstring.h"

using namespace PBSupport::PropertyList;

Dictionary::Dictionary(xmlNodePtr XMLNode) : Node() {
    xmlNodePtr child;
    for (child = XMLNode->next->children; child != nullptr; child = child->next) {
        if (child->type == XML_ELEMENT_NODE) {
            const char *key = nullptr;
            if (xmlStrcmp(child->name, (xmlChar *)"key") == 0) {
                key = (const char *)xmlNodeGetContent(child);
            } else {
                switch (GetNodeTypeForXMLNode(child)) {
                    case Node::NodeType::Boolean:
                        m_map.insert_or_assign(key, std::make_shared<Boolean>(child));
                        break;
                    case Node::NodeType::String:
                        m_map.insert_or_assign(key, std::make_shared<String>(child));
                        break;
                    case Node::NodeType::Dictionary:
                        m_map.insert_or_assign(key, std::make_shared<Dictionary>(child));
                        break;
                    default:
                        break;
                }
            }
        }
    }
}
