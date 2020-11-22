#include <iostream>
#include <map>
#include <fstream>

#include "Tag.h"
#include "Formatter.h"
#include "Reader.h"
#include "Executor.h"

using String = std::string;

void freeMemory(std::map<String, Tag*>& tags) {
    std::map<String, Tag*>::iterator iterator = tags.begin();
    while (iterator != tags.end()) {
        if (iterator->second)
            freeMemory(iterator->second->m_Children);
        delete (iterator->second);
        iterator++;
    }
}

int main(int argsl, char** args) {
	if (argsl < 2) {
		std::cout << "Insert the input file path as execution argument." << std::endl;
		return 1;
	}
	
    // cin para arquivo
    std::ifstream in = std::ifstream(args[1]);
    std::cin.rdbuf(in.rdbuf());

    int qtdLinesCode, qtdQueries;
    std::cin >> qtdLinesCode >> qtdQueries;
    
    std::map<String, Tag*> tags;
    Tag* currentTag = nullptr;
    String input;

    // Read Tags
    for (int i = 0; i < qtdLinesCode; i++) {
        Reader::readTag(input, currentTag);

        if (currentTag && !currentTag->m_Parent) // Adds tag to root when it has no parent
            tags[currentTag->m_Name] = currentTag;
    }

    // Execute queries
    for (int i = 0; i < qtdQueries; i++) {
        Reader::readNewWord(input);
        std::cout << Executor::executeQuery(input, tags) << std::endl;
    }

    freeMemory(tags);
    return 0;
}
