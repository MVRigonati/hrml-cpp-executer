#pragma once

#include <map>

using String = std::string;

class Tag {
public:

    String m_Name;
    std::map<String, String> m_Attributes;
    std::map<String, Tag*> m_Children;
    Tag* m_Parent;

    Tag(String name)
        : m_Name(name), m_Parent(nullptr) {};

    Tag(String name, Tag* parent)
        : m_Name(name), m_Parent(parent) {};

    void putAttribute(String name, String value);

    void addChildren(Tag* child);
    
};