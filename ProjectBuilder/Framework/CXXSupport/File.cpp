// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#include "PropertyList.hpp"
#include "libxml/parser.h"
#include "libxml/xmlstring.h"
#include <cstdio>
#include <cstring>
#include <memory>
#include <stdexcept>
#include <vector>

using namespace PBSupport::PropertyList;

File::File(const std::vector<uint8_t> &file) {
    /* setup my variables smh */
    m_rawFile = std::make_shared<std::vector<uint8_t>>(file);
    /* XML plist??? */
    if (*(file.data()) == '<') {
        m_fileType = FileType::XML;
        m_xmlDoc = xmlReadMemory((const char *)m_rawFile->data(), m_rawFile->size(), nullptr, nullptr, XML_PARSE_DTDLOAD);
        if (m_xmlDoc == nullptr) {
            throw std::runtime_error("Root XML Node is nullptr. Wtf?");
        }
        m_rootXmlNode = xmlDocGetRootElement(m_xmlDoc);
        if (m_rootXmlNode == nullptr) {
            throw std::runtime_error("Root XML Node is nullptr. Wtf?");
        }
        xmlNodePtr cur = m_rootXmlNode;
        do {
            if (xmlStrcmp(cur->name, (const xmlChar *)"plist")  == 0) {
                xmlChar *version = xmlGetProp(cur, (const xmlChar *)"version");
                if (xmlStrcmp(version, (xmlChar *)"1.0")) {
                    throw std::invalid_argument("Is there a new plist revision?");
                }
                /* A <plist></plist> will only ever have ONE child. */
                for (xmlNodePtr childNode = cur->children; childNode != nullptr; childNode = childNode->next) {
                    if (childNode->type == XML_ELEMENT_NODE) {
                        switch (GetNodeTypeForXMLNode(childNode)) {
                            case NodeType::Dictionary: {
                                m_rootNode = std::make_shared<Dictionary>(childNode);
                                break;
                            }
                            case NodeType::Array: {
                                m_rootNode = std::make_shared<Array>(childNode);
                                break;
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
            throw std::runtime_error("binary plists are unsupported for now, soz.");
        } else {
            throw std::invalid_argument("bad plist file?");
        }
    }
}

File::~File() {
    if (m_xmlDoc) {
        xmlFreeDoc(m_xmlDoc);
    }
}

bool File::SaveFile(const std::filesystem::path &FilePath) {
    auto type = m_fileType;
    if (type == FileType::XML) {
        auto xml = xmlNewDoc((xmlChar *)"1.0");
        auto plistNode = xmlNewNode(NULL, (xmlChar *)"plist");
        auto dtd = xmlNewDtd(xml, (xmlChar *)"plist", (xmlChar *)"-//Apple//DTD PLIST 1.0//EN", (xmlChar *)"http://www.apple.com/DTDs/PropertyList-1.0.dtd");
        xmlSetProp(plistNode, (xmlChar *)"version", (xmlChar *)"1.0");
        xmlDocSetRootElement(xml, (xmlNodePtr)dtd); /* Set the root element as the DTD */
        xmlAddSibling((xmlNodePtr)dtd, plistNode);
        /* now let's have some fun */
        auto n = BuildXMLNodeFromNode(m_rootNode);
        xmlSaveFileEnc(FilePath.c_str(), xml, "UTF-8");
        xmlFreeDtd(dtd);
    } else {
        throw std::runtime_error("sorry, no bplist or any other kind of plist here.");
    }
    return false;
}
