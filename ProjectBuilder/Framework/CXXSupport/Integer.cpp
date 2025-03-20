// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#include "PropertyList.hpp"
#include "libxml/parser.h"
#include <string>

using namespace PBSupport::PropertyList;

Integer::Integer(xmlNodePtr XMLNode) : Node() {
    m_value = std::stoi((const char *)xmlNodeGetContent(XMLNode));
}

Integer::Integer(int value) : Node() {
    m_value = value;
}