#include "sstatus/StreamWriter.h"

void StreamWriter::writeError(const std::string& error) {
    beginStatusItemArray();

    std::string errorJson;
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
    errorJson = regex_replace(errorJson, std::regex("\n+"), "<newline>");
    // TODO: Figure out why some newline characters need the below regex to be
    // matched
    errorJson = regex_replace(errorJson, std::regex("\\\\n+"), "<newline>");

    std::cout << errorJson;

    endStatusItemArray();

    std::cout << std::flush;
}

void StreamWriter::writeStatusItem(const std::string& jsonText, bool firstItem) {
    // Remove any newline characters from the line
    std::string newText = regex_replace(jsonText, std::regex("\n+"), "");

    if (firstItem)
        std::cout << newText;
    else
        std::cout << "," << newText;
    std::cout << std::flush;
}

void StreamWriter::initJSONStream() {
    std::string header;
    header.append("{");
    header.append("\"version\": ");
    header.append("1");
    header.append("}");
    std::cout << header;

    std::cout << "[";
}

void StreamWriter::beginStatusItemArray() {
    std::cout << "[";
}

void StreamWriter::endStatusItemArray() {
    std::cout << "],";
}
