#include "sstatus/StatusItem.h"

std::string StatusItem::getJsonText() {
    return StatusItemJsonFormatter::statusItemToJson(*this);
}

std::string StatusItem::getFullText() {
    if (interval == -1) {
        if (!persistent) {
            fullText = ShellInterpreter::interpret(script);
            persistent = true;
        }
        return fullText;
    }

    if (currentInterval > 1) {
        currentInterval--;
        return fullText;
    } else {
        fullText = ShellInterpreter::interpret(script);
        currentInterval = interval;
        return fullText;
    }
}

std::string StatusItem::getForegroundColor() {
    return foregroundColor;
}

std::string StatusItem::getBackgroundColor() {
    return backgroundColor;
}

std::string StatusItem::getBorderColor() {
    return borderColor;
}

bool StatusItem::hasSeparatorAfter() const {
    return separatorAfter;
}

std::string StatusItem::getScript() {
    return script;
}

void StatusItem::setForegroundColor(const std::string &fg) {
    foregroundColor = fg;
}

void StatusItem::setBackgroundColor(const std::string &bg) {
    backgroundColor = bg;
}

void StatusItem::setBorderColor(const std::string &b) {
    borderColor = b;
}

void StatusItem::setScript(const std::string &s) {
    script = s;
}

void StatusItem::setInterval(int i) {
    interval = i;
}

std::string StatusItem::StatusItemJsonFormatter::statusItemToJson(StatusItem &item) {
    std::string jsonString;

    jsonString.append("{");

    std::string mFullText = item.getFullText();
    if (!mFullText.empty()) {
        jsonString.append("\"full_text\": ");
        jsonString.append("\"");
        jsonString.append(mFullText);
        jsonString.append("\"");
        jsonString.append(",");
    }

    std::string mForegroundColor = item.getForegroundColor();
    if (!mForegroundColor.empty()) {
        jsonString.append("\"color\": ");
        jsonString.append("\"");
        jsonString.append(mForegroundColor);
        jsonString.append("\"");
        jsonString.append(",");
    }

    std::string mBackgroundColor = item.getBackgroundColor();
    if (!mBackgroundColor.empty()) {
        jsonString.append("\"background\": ");
        jsonString.append("\"");
        jsonString.append(mBackgroundColor);
        jsonString.append("\"");
        jsonString.append(",");
    }

    std::string mBorderColor = item.getBorderColor();
    if (!mBorderColor.empty()) {
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
    jsonString.append(item.hasSeparatorAfter() ? "true" : "false");

    jsonString.append("}");

    return jsonString;
}
