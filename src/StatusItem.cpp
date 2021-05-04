#include "sstatus/StatusItem.h"

#include <utility>

StatusItem::StatusItem(std::string s, std::string fg, std::string bg, std::string bc, const long i)
    : script(std::move(s)),
      foregroundColor(std::move(fg)),
      backgroundColor(std::move(bg)),
      borderColor(std::move(bc)),
      interval(i) {}

std::string StatusItem::getScript() {
    return script;
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

long StatusItem::getInterval() const {
    return interval;
}

bool StatusItem::hasSeparatorAfter() const {
    return separatorAfter;
}