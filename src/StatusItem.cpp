#include "sstatus/StatusItem.h"

using namespace std;

string StatusItem::getJsonText() {
	string jsonText = "";
	jsonText.append("{");

	jsonText.append("\"full_text\": ");
	jsonText.append("\"");
	jsonText.append(fullText);
	jsonText.append("\",");

	jsonText.append("\"separator\": false,");

	jsonText.append("\"separator_block_width\": 0");

	jsonText.append("}");
	return jsonText;
}

string StatusItem::getFullText() {
	return fullText;
}
