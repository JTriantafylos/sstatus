#include "sstatus/StatusItem.h"

using namespace std;

string StatusItem::getJsonText() {
    return StatusItemJsonFormatter::statusItemToJson(*this);
}

string StatusItem::getFullText() {
    if(interval == -1) {
        if(persistent == false) {
            fullText = mShellInterpreter.interpret(script);
            persistent = true;
        }
        return fullText;
    }

    if(currentInterval > 1) {
        currentInterval--;
        return fullText;
    } else {
        fullText = mShellInterpreter.interpret(script);
        currentInterval = interval;
        return fullText;
    }
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

string StatusItem::getScript() {
    return script;
}

void StatusItem::setForegroundColor(const string fg) {
    foregroundColor = fg;
}

void StatusItem::setBackgroundColor(const string bg) {
    backgroundColor = bg;
}

void StatusItem::setBorderColor(const string b) {
    borderColor = b;
}

void StatusItem::setScript(const string s) {
    script = s;
}

void StatusItem::setInterval(const int i) {
    interval = i;
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

    /*
     * TODO: Implement other StatusItem fields.
     */

    jsonString.append("\"separator\": ");
    jsonString.append(item.getSeparatorAfter() ? "true" : "false");

    jsonString.append("}");

    return jsonString;
}
