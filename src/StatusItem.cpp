/*
 * StatusItem.cpp - Status item data class
 * Copyright (C) 2020-2021 James Triantafylos
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "sstatus/StatusItem.h"

#include <utility>

StatusItem::StatusItem(std::string name,
                       std::string instance,
                       std::string script,
                       std::string foregroundColor,
                       std::string backgroundColor,
                       std::string borderColor,
                       bool separatorAfter,
                       const long interval)
    : mName(std::move(name)),
      mInstance(std::move(instance)),
      mScript(std::move(script)),
      mForegroundColor(std::move(foregroundColor)),
      mBackgroundColor(std::move(backgroundColor)),
      mBorderColor(std::move(borderColor)),
      mSeparatorAfter(separatorAfter),
      mInterval(interval) {}

std::string StatusItem::getName() const {
    return mName;
}

std::string StatusItem::getInstance() const {
    return mInstance;
}

std::string StatusItem::getScript() const {
    return mScript;
}

std::string StatusItem::getForegroundColor() const {
    return mForegroundColor;
}

std::string StatusItem::getBackgroundColor() const {
    return mBackgroundColor;
}

std::string StatusItem::getBorderColor() const {
    return mBorderColor;
}

long StatusItem::getInterval() const {
    return mInterval;
}

bool StatusItem::hasSeparatorAfter() const {
    return mSeparatorAfter;
}
