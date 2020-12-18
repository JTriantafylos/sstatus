#include "sstatus/StreamWriter.h"

using namespace std;

void StreamWriter::writeError(string error) {
    beginStatusItemArray();

	string errorJson = "";
	errorJson.append("{");
	errorJson.append("\"full_text\": ");
	errorJson.append("\"");
	errorJson.append("sstatus: ");
	errorJson.append(error);
	errorJson.append("\"");
    errorJson.append(",");
	errorJson.append("\"color\": ");
	errorJson.append("\"");
	errorJson.append("#ff0000");
	errorJson.append("\"");
	errorJson.append("}");

    // Remove any newline characters from the line
    errorJson = regex_replace(errorJson, regex("\n+"), "<newline>");
    // TODO: Figure out why some newline characters need the below regex to be matched
    errorJson = regex_replace(errorJson, regex("\\\\n+"), "<newline>");

    cout << errorJson;

    endStatusItemArray();

	cout << flush;
}

void StreamWriter::writeStatusItem(string jsonText, bool lastItem) {
    // Remove any newline characters from the line
    jsonText = regex_replace(jsonText, regex("\n+"), "");

	if(lastItem)
		cout << jsonText;
	else
		cout << jsonText << ",";
    cout << flush;
}

void StreamWriter::initJSONStream() {
	string header = "";
	header.append("{");
	header.append("\"version\": ");
	header.append("1");
	header.append("}");
	cout << header;

	cout << "[";
}

void StreamWriter::beginStatusItemArray() {
	cout << "[";
}

void StreamWriter::endStatusItemArray() {
	cout << "],";
}
