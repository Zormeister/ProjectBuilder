// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#include "PropertyList.hpp"
#include "libxml/parser.h"
#include "libxml/xmlerror.h"
#include "libxml/xmlstring.h"
#include <cstdio>
#include <cstring>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <vector>

using namespace PBSupport::PropertyList;

#define TMP_BUF_SIZE 256
void error(void *ctx, const char *msg, ...) {
   char string[TMP_BUF_SIZE];
   va_list arg_ptr;

   va_start(arg_ptr, msg);
   vsnprintf(string, TMP_BUF_SIZE, msg, arg_ptr);
   va_end(arg_ptr);
   std::cout << string << std::endl;
   return;
}

File::File(const std::vector<uint8_t> &file) {
    /* setup my variables smh */
    m_rawFile = std::make_unique<std::vector<uint8_t>>(file);

    xmlSetGenericErrorFunc(NULL, error);
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
            printf("what the sigma (<%p>)\n", cur);
            printf("node: %s\n", cur->name);
            printf("child type: %d\n", cur->type);
            if (xmlStrcmp(cur->name, (const xmlChar *)"plist")  == 0) {
                xmlChar *version = xmlGetProp(cur, (const xmlChar *)"version");
                printf("plist version: %s\n", version);
                /* A <plist></plist> will only ever have ONE child. */
                xmlNodePtr rootNode = cur->children;
                /* please tell me how 2 get funny name */
                /*
                 * <dict>
                 * </dict>
                 */
                printf("child? <%p> name: %s\n", rootNode, rootNode->name);
                printf("child type: %d\n", rootNode->type);
                printf("content?: %s", xmlNodeGetContent(rootNode));
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
