// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#include <cpplist/cpplist.hpp>

#include <ctime>
#include <cstring>
#include <stdexcept>

using namespace cpplist;

Date::Date(xmlNodePtr XMLNode) : Node() {
    if (xmlStrcmp(XMLNode->name, (xmlChar *)"date") == 0) {
        m_dateString = (const char *)xmlNodeGetContent(XMLNode);
    } else {
        throw std::invalid_argument("How did we get here? The XML Node wasn't named 'date'.");
    }
}

Date::Date() : Node() {
    throw std::runtime_error("i am so sorry i have not implemented this yet\n");
}

const std::string &Date::GetFormattedValue() {
    std::string tmp = m_dateString;
    /* 2025-03-08 T 04:59:40 Z */
    std::tm tm;
    tm.tm_year = stoi(tmp.substr(0, 4)) - 1900;
    tm.tm_mon = stoi(tmp.substr(5, 2)) - 1;
    tm.tm_mday = stoi(tmp.substr(8, 2));
    tm.tm_hour = stoi(tmp.substr(11, 2));
    tm.tm_min = stoi(tmp.substr(14, 2));
    tm.tm_sec = stoi(tmp.substr(17, 2));
    char date[32];
    strftime(date, 32, "%+", &tm);
    m_saneFormatString = date;
    return m_saneFormatString;
}
