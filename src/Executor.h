#pragma once

#include <iostream>
#include <map>
#include <sstream>
#include "Tag.h"
#include "Reader.h"

#define TAG_DELIMITER '.'
#define NOT_FOUND "Not Found!"
#define TILDE '~'

using String = std::string;

class Executor {

public:
	static String executeQuery(const String& input, std::map<String, Tag*>& tags);
	
private:
	static String searchAttributeOrAnotherTag(std::stringstream& stream, Tag* tag, String& token);
	static void extractTagAndAttributeNames(String& tag, String& att, String& token);
	
};