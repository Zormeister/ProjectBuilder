// Copyright (C) 2025 Zormeister, All rights reserved. Licensed under the BSD 3-Clause License.

#ifndef PROJECTBUILDER_SUPPORT_PROPERTYLIST_HPP
#define PROJECTBUILDER_SUPPORT_PROPERTYLIST_HPP

#ifdef __cplusplus

#if __APPLE__ == 0
#include "SupportBase.hpp"
#else
#include <PBSupport/SupportBase.hpp>
#endif

#include <map>
#include <string>
#include <memory>
#include <vector>
#include <optional>
#include <filesystem>

#include <libxml/dict.h>
#include <libxml/tree.h>

/* this is designed to only serialise in memory. i do not know if i even WANT to try and implement a file saving impl */

namespace PBSupport {

namespace PropertyList {

struct BinaryPlistHeader {
    char magic[5]; // bplist00
    char version[2];
};

enum struct NodeType {
    Array,
    Boolean,
    Data,
    Date,
    Dictionary,
    Integer,
    String,
    Unknown,
};

class Node {

    public:

    virtual NodeType GetNodeType() = 0;
};

NodeType GetNodeTypeForXMLNode(xmlNodePtr Node);
xmlNodePtr BuildXMLNodeFromNode(std::shared_ptr<Node> Node);

class String : public Node {

    public:
    String(xmlNodePtr XMLNode);
    String(const std::string &String);

    virtual NodeType GetNodeType() override { return NodeType::String; }

    const std::string &GetString() { return m_string; };

    private:
    std::string m_string;
};

class Array : public Node {

    public:
    Array(xmlNodePtr XMLNode);
    Array(std::vector<std::shared_ptr<Node>> Vector);

    virtual NodeType GetNodeType() override { return NodeType::Array; }

    size_t GetSize() { return m_array.size(); };

    std::shared_ptr<Node> GetNodeAtIndex(size_t index) { return m_array[index]; };

    void AddElement(std::shared_ptr<Node> Node) { m_array.push_back(Node); }
    void RemoveElement(size_t Index) { m_array.erase(m_array.begin() + Index); }

    private:
    std::vector<std::shared_ptr<Node>> m_array;
};

class Dictionary : public Node {

    public:
    Dictionary(xmlNodePtr XMLNode);
    Dictionary(std::map<std::string, std::shared_ptr<Node>> Entries);

    virtual NodeType GetNodeType() override { return NodeType::Dictionary; }

    bool ContainsKey(const std::string &Key);

    /* large line. oof. */
    std::optional<std::shared_ptr<Node>> GetNode(const std::string &Key);

    auto GetIterator() { return m_map.begin(); }
    auto GetIteratorEnd() { return m_map.end(); }

    auto GetMap() { return m_map; }

    private:
    std::map<std::string, std::shared_ptr<Node>> m_map;
};

class Date : public Node {

    public:
    Date(xmlNodePtr XMLNode); /* Use XML Node for instanciation */
    Date(const std::string &DateString); /* HAS to be an RFC3339 encoded timestamp. */
    Date(); /* Get the current time & use that as our date */

    virtual NodeType GetNodeType() override { return NodeType::Date; }

    const std::string &GetValue() { return m_dateString; }

    const std::string &GetFormattedValue();

    private:
    std::string m_dateString;
    std::string m_saneFormatString;
};

class Boolean : public Node {
    public:
    Boolean(xmlNodePtr XMLNode);
    Boolean(bool value);

    virtual NodeType GetNodeType() override { return NodeType::Boolean; }

    bool GetValue() { return m_value; }

    private:
    bool m_value;
};

class Integer : public Node {
    public:
    Integer(xmlNodePtr XMLNode);
    Integer(int value);

    virtual NodeType GetNodeType() override { return NodeType::Integer; }

    int GetValue() { return m_value; }

    private:
    int m_value;
};

class Data : public Node {
    public:
    Data(xmlNodePtr XMLNode);
    Data(const std::vector<uint8_t> &Data);

    virtual NodeType GetNodeType() override { return NodeType::Data; }

    const std::vector<uint8_t> &GetData() { return m_data; };

    const size_t GetSize() { return m_data.size(); };

    std::vector<char> EncodeData(); /* Encode stored data to base64 */

    private:
    std::vector<uint8_t> m_data;
};

const char *EncodeDataNode(std::shared_ptr<PropertyList::Data> Data);

class File {
    public:

    enum struct FileType {
        XML,
        BinaryPlist,
    };

    File(const std::vector<uint8_t> &file);
    File(NodeType RootNodeType, FileType Type = FileType::XML);
    ~File();

    std::shared_ptr<Node> GetRootNode() { return m_rootNode; }

    bool SaveFile(const std::filesystem::path &FilePath);

    private:
    std::shared_ptr<std::vector<uint8_t>> m_rawFile; // was this necessary - does the new vector copy data from the old one???
    std::shared_ptr<Node> m_rootNode;
    xmlDocPtr m_xmlDoc;
    xmlNodePtr m_rootXmlNode;
    FileType m_fileType;
};

}

}

#endif

#endif
