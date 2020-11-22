#include "Executor.h"

void Executor::extractTagAndAttributeNames(String& tag, String& att, String& token) {
    std::stringstream stream = std::stringstream(token);
    std::getline(stream, tag, TILDE);
    std::getline(stream, att, TILDE);
}

String Executor::executeQuery(const String& input, std::map<String, Tag*>& tags) {
	std::stringstream streamInput(input);
    String token, result;
    std::getline(streamInput, token, TAG_DELIMITER);

    if (token.find(TILDE) == String::npos) {
        result = (tags[token])
            ? Executor::searchAttributeOrAnotherTag(streamInput, tags[token], token)
            : NOT_FOUND;
    } else {
        String tagName, tagAttribute;
        Executor::extractTagAndAttributeNames(tagName, tagAttribute, token);
        result = Reader::readAttribute(tags[tagName], tagName, tagAttribute);
    }

    return result;
}

String Executor::searchAttributeOrAnotherTag(std::stringstream& stream, Tag* tag, String& token){
    String result;
    std::getline(stream, token, TAG_DELIMITER);

    if (token.find(TILDE) == String::npos) {
        result = (tag && tag->m_Children[token])
            ? searchAttributeOrAnotherTag(stream, tag->m_Children[token], token)
            : NOT_FOUND;
    } else {
        String tagName, tagAttribute;
        Executor::extractTagAndAttributeNames(tagName, tagAttribute, token);
        result = Reader::readAttribute(tag->m_Children[tagName], tagName, tagAttribute);
    }

    return result;
}
