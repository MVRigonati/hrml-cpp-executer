#pragma once

#include <iostream>
#include "Tag.h"
#include "Formatter.h"

#define NOT_FOUND "Not Found!"
#define OPEN_TAG '<'
#define CLOSE_TAG '>'
#define BAR '/'

using String = std::string;

class Reader {

public:
	static String readAttribute(Tag* tag, const String& tagName, const String& tagAttribute);
	static void readTag(String& input, Tag*& currentTag);
	static void readNewWord(String& output);
	
};