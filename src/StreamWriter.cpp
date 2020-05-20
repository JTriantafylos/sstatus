#include "sstatus/StreamWriter.h"

using namespace std;

void StreamWriter::writeStatusItem(string jsonText, bool lastItem) {
	if(lastItem)
		cout << jsonText;
	else
		cout << jsonText << ",";
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
