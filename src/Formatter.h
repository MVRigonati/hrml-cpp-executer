#pragma once

#include <iostream>

#define CLOSE_TAG '>'

using String = std::string;

class Formatter {

public:
	static String formatTagName(const String& input);
	static String formatAttributeValue(const String& value);
	
private:
	static String shrinkStringIfCloseTag(const String& input, const int& caseWithCloseTag, const int& otherCase);
	
};