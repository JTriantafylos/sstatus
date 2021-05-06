#include "sstatus/StatusItem.h"

#include <utility>

StatusItem::StatusItem(std::string script, std::string foregroundColor, std::string backgroundColor, std::string borderColor, const long interval)
    : mScript(std::move(script)),
      mForegroundColor(std::move(foregroundColor)),
      mBackgroundColor(std::move(backgroundColor)),
      mBorderColor(std::move(borderColor)),
      mInterval(interval) {}

std::string StatusItem::getScript() {
    return mScript;
}

std::string StatusItem::getForegroundColor() {
    return mForegroundColor;
}

std::string StatusItem::getBackgroundColor() {
    return mBackgroundColor;
}

std::string StatusItem::getBorderColor() {
    return mBorderColor;
}

long StatusItem::getInterval() const {
    return mInterval;
}

bool StatusItem::hasSeparatorAfter() const {
    return mSeparatorAfter;
}