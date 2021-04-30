#include "sstatus/StatusItem.h"

#include <utility>

StatusItem::StatusItem(std::string s, std::string fg, std::string bg, std::string bc, const long i)
    : script(std::move(s)),
      foregroundColor(std::move(fg)),
      backgroundColor(std::move(bg)),
      borderColor(std::move(bc)),
      interval(i) {}

std::string StatusItem::getJsonText() {
    return StatusItemJsonFormatter::statusItemToJson(*this);
}

std::string StatusItem::getFullText() {
    fullText = ShellInterpreter::interpret(script);
    return fullText;
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

long StatusItem::getInterval() const {
    return interval;
}

std::string StatusItem::StatusItemJsonFormatter::statusItemToJson(StatusItem& item) {
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
