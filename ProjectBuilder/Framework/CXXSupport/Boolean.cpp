// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#include "PropertyList.hpp"
#include "libxml/parser.h"
#include "libxml/xmlstring.h"
#include <stdexcept>

using namespace PBSupport::PropertyList;

Boolean::Boolean(xmlNodePtr XMLNode) : Node() {
    if (xmlStrcmp(XMLNode->name, (xmlChar *)"true") == 0) {
        m_value = true;
    } else if (xmlStrcmp(XMLNode->name, (xmlChar *)"false") == 0) {
        m_value = false;
    } else {
        throw std::runtime_error("This isn't supposed to happen - WTF?");
    }
}

Boolean::Boolean(bool value) : Node() {
    m_value = value;
}
