// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#ifndef PROJECTBUILDER_SUPPORT_PROPERTYLIST_HPP
#define PROJECTBUILDER_SUPPORT_PROPERTYLIST_HPP

#include "SupportBase.hpp"

#include <string>
#include <memory>
#include <vector>

#include <libxml/dict.h>
#include <libxml/tree.h>

SUPPORT_BEGIN_NS

struct BinaryPlistHeader {
    char magic[8]; // bplist00
};

class PropertyListNode {

    public:
    enum struct NodeType {
        Array,
        Boolean,
        Data,
        Date,
        Dictionary,
        Integer,
        String,
        Real,
    };

    virtual NodeType GetNodeType() = 0;

    protected:
    std::string m_nodeKey;
};

class PropertyListString : public PropertyListNode {

    public:
    virtual NodeType GetNodeType() override { return NodeType::String; }

    std::string GetString();

    private:
    std::string m_string;
};

class PropertyListArray : public PropertyListNode {

    public:
    virtual NodeType GetNodeType() override { return NodeType::Array; }

    size_t GetSize();

    std::shared_ptr<PropertyListNode> GetNodeAtIndex(size_t index);

    private:
    std::vector<std::shared_ptr<PropertyListNode>> m_array;
};


class PropertyListFile {
    public:

    PropertyListFile(const std::vector<uint8_t> &file);

    std::shared_ptr<PropertyListNode> GetRootNode();

    private:
    std::unique_ptr<std::vector<uint8_t>> m_rawFile;
    std::shared_ptr<PropertyListNode> m_rootNode;
    xmlDocPtr m_xmlDoc;
    xmlNodePtr m_rootXmlNode;
};

SUPPORT_END_NS

#endif
