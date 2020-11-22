
#include "Tag.h"

void Tag::putAttribute(String name, String value) {
	m_Attributes[name] = value;
}

void Tag::addChildren(Tag* child) {
	m_Children[child->m_Name] = child;
}
