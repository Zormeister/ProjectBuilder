// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#ifndef PROJECTBUILDER_SUPPORT_PROPERTYLIST_HPP
#define PROJECTBUILDER_SUPPORT_PROPERTYLIST_HPP

#include "SupportBase.hpp"

#include <string>

#if TAREGT_LINUX || 1
#include <libxml/dict.h>
#endif

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

SUPPORT_END_NS

#endif