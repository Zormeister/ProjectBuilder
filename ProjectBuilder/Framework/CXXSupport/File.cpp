// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#include "PropertyList.hpp"
#include "libxml/parser.h"
#include "libxml/xmlstring.h"
#include <cstdio>
#include <cstring>
#include <memory>
#include <stdexcept>
#include <system_error>
#include <vector>

using namespace PBSupport::PropertyList;

File::File(const std::vector<uint8_t> &file) {
    /* setup my variables smh */
    m_rawFile = std::make_unique<std::vector<uint8_t>>(file);
    /* XML plist??? */
    if (*(file.data()) == '<') {
        m_xmlDoc = xmlReadMemory((const char *)m_rawFile->data(), m_rawFile->size(), nullptr, nullptr, XML_PARSE_DTDLOAD);
        if (m_xmlDoc == nullptr) {
            throw std::system_error();
        }
        m_rootXmlNode = xmlDocGetRootElement(m_xmlDoc);
        if (m_rootXmlNode == nullptr) {
            throw std::system_error();
        }
        xmlNodePtr cur = m_rootXmlNode;
        do {
            if (xmlStrcmp(cur->name, (const xmlChar *)"plist")  == 0) {
                xmlChar *version = xmlGetProp(cur, (const xmlChar *)"version");
                printf("plist version: %s\n", version);
                /* A <plist></plist> will only ever have ONE child. */
                for (xmlNodePtr childNode = cur->children; childNode != nullptr; childNode = childNode->next) {
                    if (childNode->type == XML_ELEMENT_NODE) {
                        switch (GetNodeTypeForXMLNode(childNode)) {
                            case Node::NodeType::Dictionary: {
                                m_rootNode = std::make_shared<Dictionary>(std::nullopt, childNode);
                                break;
                            }
                            case Node::NodeType::Array: {
                                // do smthn
                            }
                            default:
                                throw std::invalid_argument("Root node shouldn't be anything that isn't a dictionary or array. WTF?");
                        }
                    }
                }
            }
            cur = cur->next;
        } while (cur != nullptr);
    } else {
        BinaryPlistHeader *hdr = (BinaryPlistHeader *)file.data();
        if (strncmp(hdr->magic, "bplist", 5) == 0) {
            
        } else {
            throw std::invalid_argument("bad plist file?");
        }
    }
}

File::~File() {
    /* At this point, something needs to signal to the lower nodes that their data is about to be taken away. */
    if (m_xmlDoc) {
        xmlFreeDoc(m_xmlDoc);
    }
}