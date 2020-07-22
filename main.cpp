#include <iostream>
#include <map>
#include <sstream>
#include <fstream>

#define OPEN_TAG '<'
#define CLOSE_TAG '>'
#define DOUBLE_QUOTES '\"'
#define TAG_DELIMITER '.'
#define NOT_FOUND "Not Found!"
#define TILDE '~'
#define BAR '/'

using namespace std;
using String = std::string;

class Tag {
public:

    String m_Name;
    map<String, String> m_Attributes;
    map<String, Tag*> m_Children;
    Tag* m_Parent;

    Tag(String name)
        : m_Name(name), m_Parent(nullptr) {};

    Tag(String name, Tag* parent)
        : m_Name(name), m_Parent(parent) {};

    void putAttribute(String name, String value) {
        m_Attributes[name] = value;
    }

    void addChildren(Tag* child) {
        m_Children[child->m_Name] = child;
    }
    
};

String executeQuery(std::stringstream& streamInput, Tag* currentTag);

void readNewWord(String& output) {
    cin >> output;
}

String shrinkStringIfCloseTag(const String& input, const int& caseWithCloseTag, const int& otherCase) {
    const int numberCharsToDelete = (input.back() == CLOSE_TAG) ? caseWithCloseTag : otherCase;
    return (input.substr(1, input.length()-numberCharsToDelete));
}

String formatTagName(const String& input) {
    return shrinkStringIfCloseTag(input, 2, 1);
}

String formatAttributeValue(String& value) {
    return shrinkStringIfCloseTag(value, 3, 2);
}

String executeQuery(std::stringstream& streamInput, Tag* currentTag);

void extractTagAndAttributeNames(String& tag, String& att, String& token) {
    std::stringstream stream = std::stringstream(token);
    std::getline(stream, tag, TILDE);
    std::getline(stream, att, TILDE);
}

String readAttribute(Tag* tag, const String& tagName, const String& tagAttribute) {
    return (tag && tag->m_Attributes[tagAttribute].size() > 0)
        ? tag->m_Attributes[tagAttribute]
        : NOT_FOUND;
}

String readAttributeOrAnotherTag(std::stringstream& stream, Tag* tag, String& token) {
    String result;
    std::getline(stream, token, TAG_DELIMITER);

    if (token.find(TILDE) == String::npos) {
        result = (tag && tag->m_Children[token])
            ? readAttributeOrAnotherTag(stream, tag->m_Children[token], token)
            : NOT_FOUND;
    } else {
        String tagName, tagAttribute;
        extractTagAndAttributeNames(tagName, tagAttribute, token);
        result = readAttribute(tag->m_Children[tagName], tagName, tagAttribute);
    }

    return result;
}

String executeQuery(const String& input, map<String, Tag*>& tags) {
    std::stringstream streamInput(input);
    String token, result;
    std::getline(streamInput, token, TAG_DELIMITER);

    if (token.find(TILDE) == String::npos) {
        result = (tags[token])
            ? readAttributeOrAnotherTag(streamInput, tags[token], token)
            : NOT_FOUND;
    } else {
        String tagName, tagAttribute;
        extractTagAndAttributeNames(tagName, tagAttribute, token);
        result = readAttribute(tags[tagName], tagName, tagAttribute);
    }

    return result;
}

void freeMemory(map<String, Tag*>& tags) {
    map<String, Tag*>::iterator iterator = tags.begin();
    while (iterator != tags.end()) {
        if (iterator->second)
            freeMemory(iterator->second->m_Children);
        delete (iterator->second);
        iterator++;
    }
}

void readTag(String& input, Tag*& currentTag) {
    do {
        readNewWord(input);

        if (input.at(0) == OPEN_TAG) {
            if (input.at(1) == BAR && input.back() == CLOSE_TAG) {
                currentTag = currentTag->m_Parent;
            } else {
                // Create new Tag
                const String tagName = formatTagName(input);
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
            const String pValue = formatAttributeValue(input);

            currentTag->putAttribute(pName, pValue);
        }
    } while (input.back() != CLOSE_TAG);
}

int main() {
    // cin para arquivo
    std::ifstream in = std::ifstream("in.txt");
    std::streambuf *cinbuf = std::cin.rdbuf();
    std::cin.rdbuf(in.rdbuf());

    int qtdLinesCode, qtdQueries;
    cin >> qtdLinesCode >> qtdQueries;
    
    map<String, Tag*> tags;
    Tag* currentTag = nullptr;
    String input;

    // Read Tags
    for (int i = 0; i < qtdLinesCode; i++) {
        readTag(input, currentTag);

        if (currentTag && !currentTag->m_Parent)// Adds tag to root when it has no parent
            tags[currentTag->m_Name] = currentTag;
    }

    // Execute queries
    for (int i = 0; i < qtdQueries; i++) {
        readNewWord(input);
        cout << executeQuery(input, tags) << endl;
    }

    freeMemory(tags);
    return 0;
}
