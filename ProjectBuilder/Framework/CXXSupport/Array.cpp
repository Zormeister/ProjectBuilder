//
//  Array.cpp
//  PBSupport
//
//  Created by Zormeister on 7/3/2025.
//

#include "PropertyList.hpp"

using namespace PBSupport::PropertyList;

Array::Array(xmlNodePtr XMLNode) : Node() {
    xmlNodePtr child;
    for (child = XMLNode->children; child != nullptr; child = child->next) {
        if (child->type == XML_ELEMENT_NODE) {
            switch (GetNodeTypeForXMLNode(child)) {
                case Node::NodeType::Array:
                    m_array.push_back(std::make_shared<Array>(child));
                    break;
                case Node::NodeType::Boolean:
                    m_array.push_back(std::make_shared<Boolean>(child));
                    break;
                case Node::NodeType::Data:
                    m_array.push_back(std::make_shared<Data>(child));
                    break;
                case Node::NodeType::Date:
                    m_array.push_back(std::make_shared<Date>(child));
                    break;
                case Node::NodeType::Dictionary:
                    m_array.push_back(std::make_shared<Dictionary>(child));
                    break;
                case Node::NodeType::Integer:
                    m_array.push_back(std::make_shared<Integer>(child));
                    break;
                case Node::NodeType::String:
                    m_array.push_back(std::make_shared<String>(child));
                    break;
                default:
                    break;
            }
        }
    }
}
