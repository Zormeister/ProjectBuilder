// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#include <cpplist/cpplist.hpp>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <libxml/parser.h>
#define BUFFERSIZE BUFSIZ
#include <b64/decode.h>
#include <b64/encode.h>
#include <memory>
#include <vector>

using namespace cpplist;

Data::Data(xmlNodePtr XMLNode) : Node() {
    auto data = xmlNodeGetContent(XMLNode);
    base64::decoder dec;
    m_data.reserve(strlen((const char *)data));
    dec.decode((const char *)data, strlen((const char *)data), (char *)m_data.data());
    printf("%s\n", m_data.data());
}

Data::Data(const std::vector<uint8_t> &Data) : Node() {
    // is there a safe way to do this or is this safe
    // OOP is messing with my brain more than
    // the OOPness of IOKit ever did holy hell
    m_data = Data;
}

// istg if someone puts in a massive amount of data such as a whole kernel binary i will shoot you
std::vector<char> Data::EncodeData() {
    std::vector<char> vec;
    vec.reserve(((4 * m_data.size() / 3) + 3) & ~3);
    base64::encoder enc;
    enc.encode((char *)m_data.data(), m_data.size(), vec.data());
    return vec;
}
