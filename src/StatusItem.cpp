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

#include <optional>
#include <utility>

StatusItem::StatusItem(std::string name,
                       std::string instance,
                       std::string script,
                       std::optional<StatusItem::Color> foregroundColor,
                       std::optional<StatusItem::Color> backgroundColor,
                       std::optional<StatusItem::Color> borderColor,
                       bool separatorAfter,
                       std::optional<std::chrono::milliseconds> interval)
    : mName(std::move(name)),
      mInstance(std::move(instance)),
      mScript(std::move(script)),
      mForegroundColor(foregroundColor),
      mBackgroundColor(backgroundColor),
      mBorderColor(borderColor),
      mSeparatorAfter(separatorAfter),
      mInterval(interval) {}

StatusItem::StatusItem(const StatusItem& other) {
    std::lock_guard otherLock(other.mMutex);

    mText = other.mText;
    mName = other.mName;
    mInstance = other.mInstance;
    mScript = other.mScript;
    mForegroundColor = other.mForegroundColor;
    mBackgroundColor = other.mBackgroundColor;
    mBorderColor = other.mBorderColor;
    mSeparatorAfter = other.mSeparatorAfter;
    mInterval = other.mInterval;
}

StatusItem::StatusItem(StatusItem&& other) noexcept {
    std::lock_guard otherLock(other.mMutex);

    mText = std::move(other.mText);
    mName = std::move(other.mName);
    mInstance = std::move(other.mInstance);
    mScript = std::move(other.mScript);
    mForegroundColor = std::move(other.mForegroundColor);
    mBackgroundColor = std::move(other.mBackgroundColor);
    mBorderColor = std::move(other.mBorderColor);
    mSeparatorAfter = other.mSeparatorAfter;
    mInterval = other.mInterval;
}

StatusItem& StatusItem::operator=(const StatusItem& other) {
    if (this != &other) {
        std::scoped_lock lock(mMutex, other.mMutex);

        mText = other.mText;
        mName = other.mName;
        mInstance = other.mInstance;
        mScript = other.mScript;
        mForegroundColor = other.mForegroundColor;
        mBackgroundColor = other.mBackgroundColor;
        mBorderColor = other.mBorderColor;
        mSeparatorAfter = other.mSeparatorAfter;
        mInterval = other.mInterval;
    }
    return *this;
}

StatusItem& StatusItem::operator=(StatusItem&& other) noexcept {
    if (this != &other) {
        std::scoped_lock lock(mMutex, other.mMutex);

        mText = std::move(other.mText);
        mName = std::move(other.mName);
        mInstance = std::move(other.mInstance);
        mScript = std::move(other.mScript);
        mForegroundColor = other.mForegroundColor;
        mBackgroundColor = other.mBackgroundColor;
        mBorderColor = other.mBorderColor;
        mSeparatorAfter = other.mSeparatorAfter;
        mInterval = other.mInterval;
    }
    return *this;
}

void StatusItem::setText(const std::string& text) {
    std::lock_guard lock(mMutex);
    mText = text;
}

std::string StatusItem::getText() const {
    std::lock_guard lock(mMutex);
    return mText;
}

std::string StatusItem::getName() const {
    std::lock_guard lock(mMutex);
    return mName;
}

std::string StatusItem::getInstance() const {
    std::lock_guard lock(mMutex);
    return mInstance;
}

std::string StatusItem::getScript() const {
    std::lock_guard lock(mMutex);
    return mScript;
}

std::optional<StatusItem::Color> StatusItem::getForegroundColor() const {
    std::lock_guard lock(mMutex);
    return mForegroundColor;
}

std::optional<StatusItem::Color> StatusItem::getBackgroundColor() const {
    std::lock_guard lock(mMutex);
    return mBackgroundColor;
}

std::optional<StatusItem::Color> StatusItem::getBorderColor() const {
    std::lock_guard lock(mMutex);
    return mBorderColor;
}

std::optional<std::chrono::milliseconds> StatusItem::getInterval() const {
    std::lock_guard lock(mMutex);
    return mInterval;
}

bool StatusItem::hasSeparatorAfter() const {
    std::lock_guard lock(mMutex);
    return mSeparatorAfter;
}
