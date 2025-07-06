// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#include <cpplist/cpplist.hpp>
#include <string>

using namespace cpplist;

Integer::Integer(xmlNodePtr XMLNode) : Node() {
    m_value = std::stoi((const char *)xmlNodeGetContent(XMLNode));
}

Integer::Integer(int value) : Node() {
    m_value = value;
}
