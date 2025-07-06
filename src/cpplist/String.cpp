// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#include <cpplist/cpplist.hpp>

using namespace cpplist;

String::String(xmlNodePtr XMLValueNode) : Node() {
    m_string = (const char *)xmlNodeGetContent(XMLValueNode); /* Our value should just be the string given back here. */
}

String::String(const std::string &String) : Node() {
    m_string = String.c_str();
}
