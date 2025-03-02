// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#ifndef PROJECTBUILDER_SUPPORT_PROPERTYLIST_HPP
#define PROJECTBUILDER_SUPPORT_PROPERTYLIST_HPP

#include "SupportBase.hpp"

#include <string>
#include <memory>

#include <libxml/dict.h>

SUPPORT_BEGIN_NS

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

class PropertyListFile {
    public:

    PropertyListFile(std::vector<uint8_t> file);

    std::shared_ptr<PropertyListNode> GetRootNode();

    private:
    std::unique_ptr<std::vector<uint8_t>> m_rawFile;
    std::shared_ptr<PropertyListNode> m_rootNode;
};

SUPPORT_END_NS

#endif
