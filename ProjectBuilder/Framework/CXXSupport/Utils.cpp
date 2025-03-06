// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#include "PropertyList.hpp"

using namespace PBSupport::PropertyList;

Node::NodeType GetNodeTypeForXMLNode(xmlNodePtr node) {
    if (xmlStrcmp(node->name, (xmlChar *)"dict") == 0) {
        return Node::NodeType::Dictionary;
    } else if (xmlStrcmp(node->name, (xmlChar *)"array") == 0) {
        return Node::NodeType::Array;
    } else if (xmlStrcmp(node->name, (xmlChar *)"string") == 0) {
        return Node::NodeType::String;
    } else if (xmlStrcmp(node->name, (xmlChar *)"true") == 0 || xmlStrcmp(node->name, (xmlChar *)"false") == 0) {
        return Node::NodeType::Boolean;
    } else if (xmlStrcmp(node->name, (xmlChar *)"date") == 0) {
        return Node::NodeType::Date;
    } else if (xmlStrcmp(node->name, (xmlChar *)"integer") == 0) {
        return Node::NodeType::Integer;
    }

    return Node::NodeType::Unknown;
}