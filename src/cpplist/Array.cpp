//
//  Array.cpp
//  PBSupport
//
//  Created by Zormeister on 7/3/2025.
//

#include <cpplist/cpplist.hpp>

using namespace cpplist;

Array::Array(xmlNodePtr XMLNode) : Node() {
    xmlNodePtr child;
    for (child = XMLNode->children; child != nullptr; child = child->next) {
        if (child->type == XML_ELEMENT_NODE) {
            switch (GetNodeTypeForXMLNode(child)) {
                case NodeType::Array:
                    m_array.push_back(std::make_shared<Array>(child));
                    break;
                case NodeType::Boolean:
                    m_array.push_back(std::make_shared<Boolean>(child));
                    break;
                case NodeType::Data:
                    m_array.push_back(std::make_shared<Data>(child));
                    break;
                case NodeType::Date:
                    m_array.push_back(std::make_shared<Date>(child));
                    break;
                case NodeType::Dictionary:
                    m_array.push_back(std::make_shared<Dictionary>(child));
                    break;
                case NodeType::Integer:
                    m_array.push_back(std::make_shared<Integer>(child));
                    break;
                case NodeType::String:
                    m_array.push_back(std::make_shared<String>(child));
                    break;
                default:
                    break;
            }
        }
    }
}
