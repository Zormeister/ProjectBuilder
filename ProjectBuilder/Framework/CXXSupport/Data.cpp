// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#include "PropertyList.hpp"
#include <cstdio>
#include <cstring>
#include <libxml/parser.h>
#include <b64/decode.h>
#include <vector>

using namespace PBSupport::PropertyList;

Data::Data(xmlNodePtr XMLNode) : Node() {
    auto data = xmlNodeGetContent(XMLNode);
    base64::decoder dec;
    m_data.reserve(strlen((const char *)data));
    dec.decode((const char *)data, strlen((const char *)data), (char *)m_data.data());
    printf("%s\n", m_data.data());
}