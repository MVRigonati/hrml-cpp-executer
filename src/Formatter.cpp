#include "Formatter.h"

String Formatter::formatAttributeValue(const String& value) {
	return Formatter::shrinkStringIfCloseTag(value, 3, 2);
}

String Formatter::formatTagName(const String& input) {
	return Formatter::shrinkStringIfCloseTag(input, 2, 1);
}

String Formatter::shrinkStringIfCloseTag(const String& input, const int& caseWithCloseTag, const int& otherCase) {
    const int numberCharsToDelete = (input.back() == CLOSE_TAG) ? caseWithCloseTag : otherCase;
    return (input.substr(1, input.length() - numberCharsToDelete));
}