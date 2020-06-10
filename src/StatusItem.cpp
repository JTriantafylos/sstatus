#include "sstatus/StatusItem.h"

using namespace std;

string StatusItem::getJsonText() {
    return StatusItemJsonFormatter::statusItemToJson(*this);
}

string StatusItem::getFullText() {
    return fullText;
}

string StatusItem::getForegroundColor() {
    return foregroundColor;
}

string StatusItem::getBackgroundColor() {
    return backgroundColor;
}

string StatusItem::getBorderColor() {
    return borderColor;
}

bool StatusItem::getSeparatorAfter() {
    return separatorAfter;
}

string StatusItem::StatusItemJsonFormatter::statusItemToJson(StatusItem& item) {
    string jsonString = "";

    jsonString.append("{");

    string mFullText = item.getFullText();
    if(!mFullText.empty()) {
        jsonString.append("\"full_text\": ");
        jsonString.append("\"");
        jsonString.append(mFullText);
        jsonString.append("\"");
        jsonString.append(",");
    }

    string mForegroundColor = item.getForegroundColor();
    if(!mForegroundColor.empty()) {
        jsonString.append("\"color\": ");
        jsonString.append("\"");
        jsonString.append(mForegroundColor);
        jsonString.append("\"");
        jsonString.append(",");
    }

    string mBackgroundColor = item.getBackgroundColor();
    if(!mBackgroundColor.empty()) {
        jsonString.append("\"background\": ");
        jsonString.append("\"");
        jsonString.append(mBackgroundColor);
        jsonString.append("\"");
        jsonString.append(",");
    }

    string mBorderColor = item.getBorderColor();
    if(!mBorderColor.empty()) {
        jsonString.append("\"border\": ");
        jsonString.append("\"");
        jsonString.append(mBorderColor);
        jsonString.append("\"");
        jsonString.append(",");
    }


    jsonString.append("\"separator\": ");
    jsonString.append(item.getSeparatorAfter() ? "true" : "false");

    jsonString.append("}");

    return jsonString;
}
