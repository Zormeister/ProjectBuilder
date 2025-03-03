//
//  PropertyListFile.cpp
//  ProjectBuilder
//
//  Created by Zormeister on 3/3/2025.
//

#include "PropertyList.hpp"
#include "libxml/parser.h"
#include <cstring>
#include <memory>
#include <stdexcept>
#include <vector>

using namespace PBSupport;

PropertyListFile::PropertyListFile(const std::vector<uint8_t> &file) {
    /* setup my variables smh */
    m_rawFile = std::make_unique<std::vector<uint8_t>>(file);

    /* XML plist??? */
    if (*(file.data()) == '<') {
        m_xmlDoc = xmlReadMemory((const char *)m_rawFile->data(), m_rawFile->size(), nullptr, nullptr, XML_PARSE_DTDLOAD);
        m_rootXmlNode = xmlDocGetRootElement(m_xmlDoc);
        xmlNodePtr cur = m_rootXmlNode;
        while (cur->next) {
            cur = cur->next;
        }
    } else {
        BinaryPlistHeader *hdr = (BinaryPlistHeader *)file.data();
        if (strncmp(hdr->magic, "bplist", 5) == 0) {
            
        } else {
            throw std::invalid_argument("bad plist file?");
        }
    }
}

PropertyListFile::~PropertyListFile() {
    xmlFreeDoc(m_xmlDoc);
    xmlFreeNode(m_rootXmlNode);
}
