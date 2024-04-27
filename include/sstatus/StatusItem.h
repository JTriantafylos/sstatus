/*
 * StatusItem.h - Status item data class header
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

#ifndef STATUSITEM_H
#define STATUSITEM_H

#include <mutex>
#include <string>

class StatusItem {
  public:
    StatusItem(std::string name,
               std::string instance,
               std::string script,
               std::string foregroundColor,
               std::string backgroundColor,
               std::string borderColor,
               bool separatorAfter,
               long interval);
    StatusItem(const StatusItem&);
    StatusItem(StatusItem&&) noexcept ;
    StatusItem& operator=(const StatusItem&);
    StatusItem& operator=(StatusItem&&) noexcept ;

    void setText(const std::string& text);
    std::string getText() const;
    std::string getName() const;
    std::string getInstance() const;
    std::string getScript() const;
    std::string getForegroundColor() const;
    std::string getBackgroundColor() const;
    std::string getBorderColor() const;
    [[nodiscard]] long getInterval() const;
    [[nodiscard]] bool hasSeparatorAfter() const;

  private:
    std::string mText;
    std::string mName;
    std::string mInstance;
    std::string mScript;
    std::string mForegroundColor;
    std::string mBackgroundColor;
    std::string mBorderColor;
    bool mSeparatorAfter;
    long mInterval;  // Number of milliseconds between refreshing this StatusItem
    mutable std::mutex mMutex;
};

#endif
