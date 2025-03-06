// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#ifndef PROJECTBUILDER_SUPPORT_PROPERTYLIST_HPP
#define PROJECTBUILDER_SUPPORT_PROPERTYLIST_HPP

#include "SupportBase.hpp"

#include <ctime>
#include <map>
#include <string>
#include <memory>
#include <vector>

#include <libxml/dict.h>
#include <libxml/tree.h>

/* this is designed to only serialise in memory. i do not know if i even WANT to try and implement a file saving impl */

SUPPORT_BEGIN_NS

namespace PropertyList {

struct BinaryPlistHeader {
    char magic[8]; // bplist00
};

class Node {

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

    const std::string &GetKeyName();

    protected:
    std::string m_keyName;
    xmlNodePtr m_xmlNode;
};

class String : public Node {

    public:
    virtual NodeType GetNodeType() override { return NodeType::String; }

    std::string GetString();

    private:
    std::string m_string;
};

class Array : public Node {

    public:
    virtual NodeType GetNodeType() override { return NodeType::Array; }

    size_t GetSize();

    std::shared_ptr<Node> GetNodeAtIndex(size_t index);

    void AddElement(std::shared_ptr<Node> Node);

    private:
    std::vector<std::shared_ptr<Node>> m_array;
};

class Dictionary : public Node {

    public:
    virtual NodeType GetNodeType() override { return NodeType::Array; }

    bool ContainsKey(const std::string &Key);

    std::shared_ptr<Node> GetNode(const std::string &Key);

    private:
    std::map<std::string, std::shared_ptr<Node>> m_map;
};

class Date : public Node {

    public:
    virtual NodeType GetNodeType() override { return NodeType::Date; }

    const std::string &GetValue();

    private:
    std::string m_dateString;
};

class Boolean : public Node {

    public:
    virtual NodeType GetNodeType() override { return NodeType::Boolean; }

    bool GetValue();

    private:
    bool m_value;
};

class File {
    public:

    File(const std::vector<uint8_t> &file);
    ~File();

    std::shared_ptr<Node> GetRootNode();

    private:
    std::unique_ptr<std::vector<uint8_t>> m_rawFile; // was this necessary - does the new vector copy data from the old one???
    std::shared_ptr<Node> m_rootNode;
    xmlDocPtr m_xmlDoc;
    xmlNodePtr m_rootXmlNode;
};

}

SUPPORT_END_NS

#endif
