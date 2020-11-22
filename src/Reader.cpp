#include "Reader.h"

void Reader::readNewWord(String& output) {
    std::cin >> output;
}

String Reader::readAttribute(Tag* tag, const String& tagName, const String& tagAttribute) {
	return (tag && tag->m_Attributes[tagAttribute].size() > 0)
        ? tag->m_Attributes[tagAttribute]
        : NOT_FOUND;
}

void Reader::readTag(String& input, Tag*& currentTag) {
    do {
        readNewWord(input);

        if (input.at(0) == OPEN_TAG) {
            if (input.at(1) == BAR && input.back() == CLOSE_TAG) {
                currentTag = currentTag->m_Parent;
            } else {
                // Create new Tag
                const String tagName = Formatter::formatTagName(input);
                Tag* newTag = new Tag(tagName, currentTag);
                if (currentTag)
                    currentTag->addChildren(newTag);
                currentTag = newTag;
            }
        } else {
            // Add property to Tag
            const String pName = input;
            
            readNewWord(input); // skip "="
            readNewWord(input);
            const String pValue = Formatter::formatAttributeValue(input);

            currentTag->putAttribute(pName, pValue);
        }
    } while (input.back() != CLOSE_TAG);
}