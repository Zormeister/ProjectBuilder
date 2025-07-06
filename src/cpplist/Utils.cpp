// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#include <cpplist/cpplist.hpp>
#include <libxml/parser.h>
#include <memory>
#include <cstdlib>
#include <string>
#include <unistd.h>

using namespace cpplist;

NodeType cpplist::GetNodeTypeForXMLNode(xmlNodePtr node) {
    if (xmlStrcmp(node->name, (xmlChar *)"dict") == 0) {
        return NodeType::Dictionary;
    } else if (xmlStrcmp(node->name, (xmlChar *)"array") == 0) {
        return NodeType::Array;
    } else if (xmlStrcmp(node->name, (xmlChar *)"string") == 0) {
        return NodeType::String;
    } else if (xmlStrcmp(node->name, (xmlChar *)"true") == 0 || xmlStrcmp(node->name, (xmlChar *)"false") == 0) {
        return NodeType::Boolean;
    } else if (xmlStrcmp(node->name, (xmlChar *)"date") == 0) {
        return NodeType::Date;
    } else if (xmlStrcmp(node->name, (xmlChar *)"integer") == 0) {
        return NodeType::Integer;
    } else if (xmlStrcmp(node->name, (xmlChar *)"data") == 0) {
        return NodeType::Data;
    }

    return NodeType::Unknown;
}

xmlNodePtr cpplist::BuildXMLNodeFromNode(std::shared_ptr<Node> Node) {
    switch (Node->GetNodeType()) {
        case NodeType::String: {
            auto string = std::dynamic_pointer_cast<String>(Node);
            auto xml = xmlNewNode(NULL, (xmlChar *)"string");
            xmlNodeAddContent(xml, (xmlChar *)string->GetString().c_str());
            return xml;
        }
        case NodeType::Data: {
            auto data = std::dynamic_pointer_cast<Data>(Node);
            auto xml = xmlNewNode(NULL, (xmlChar *)"data");
            xmlNodeAddContent(xml, (xmlChar *)data->EncodeData().data());
            return xml;
        }
        case NodeType::Date: {
            auto date = std::dynamic_pointer_cast<Date>(Node);
            auto xml = xmlNewNode(NULL, (xmlChar *)"date");
            xmlNodeAddContent(xml, (xmlChar *)date->GetValue().c_str());
            return xml;
        }
        case NodeType::Integer: {
            auto integer = std::dynamic_pointer_cast<Integer>(Node);
            auto xml = xmlNewNode(NULL, (xmlChar *)"integer");
            xmlNodeAddContent(xml, (xmlChar *)std::to_string(integer->GetValue()).c_str());
            return xml;
        }
        case NodeType::Boolean: {
            auto boolean = std::dynamic_pointer_cast<Boolean>(Node);
            xmlNodePtr xml;
            if (boolean->GetValue()) {
                xml = xmlNewNode(NULL, (xmlChar *)"true");
            } else {
                xml = xmlNewNode(NULL, (xmlChar *)"false");
            }
            return xml;
        }
        case NodeType::Array: {
            auto arr = std::dynamic_pointer_cast<Array>(Node);
            auto xml = xmlNewNode(NULL, (xmlChar *)"array");
            for (size_t i = 0; i < arr->GetSize(); i++) {
                auto node = arr->GetNodeAtIndex(i);
                auto child = BuildXMLNodeFromNode(node);
                xmlAddChild(xml, child);
            }
            return xml;
        }
        case NodeType::Dictionary: {
            auto dict = std::dynamic_pointer_cast<Dictionary>(Node);
            auto xml = xmlNewNode(NULL, (xmlChar *)"dict");
            for (auto iter = dict->GetIterator(); iter != dict->GetIteratorEnd(); ++iter) {
                auto key = xmlNewChild(xml, NULL, (xmlChar *)"key", (xmlChar *)iter->first.c_str());
                auto child = BuildXMLNodeFromNode(iter->second);
                xmlAddSibling(key, child);
            };
            return xml;
        }
        case NodeType::Unknown: {
            return nullptr;
        }
    }
}
