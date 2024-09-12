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

#include <format>
#include <ios>
#include <mutex>
#include <sstream>
#include <string>

class StatusItem {
  public:
    struct Color {
        uint8_t red;
        uint8_t green;
        uint8_t blue;

        std::string toHexString() {
            return std::format("#{:02X}{:02X}{:02X}", this->red, this->green, this->blue);
        }

        static Color fromHexString(const std::string& hex_string) {
            uint32_t rgb = 0;
            std::istringstream hexStringStream(hex_string);

            if (hexStringStream.peek() == '#') {
                hexStringStream.get();
            }
            hexStringStream >> std::hex >> rgb;

            return Color {
                (uint8_t)(rgb >> 16),
                (uint8_t)(rgb >> 8),
                (uint8_t)rgb
            };
        }
    };

    StatusItem(std::string name,
               std::string instance,
               std::string script,
               std::optional<StatusItem::Color> foregroundColor,
               std::optional<StatusItem::Color> backgroundColor,
               std::optional<StatusItem::Color> borderColor,
               bool separatorAfter,
               std::optional<std::chrono::milliseconds> interval);
    StatusItem(const StatusItem&);
    StatusItem(StatusItem&&) noexcept;
    StatusItem& operator=(const StatusItem&);
    StatusItem& operator=(StatusItem&&) noexcept ;

    void setText(const std::string& text);
    std::string getText() const;
    std::string getName() const;
    std::string getInstance() const;
    std::string getScript() const;
    std::optional<StatusItem::Color> getForegroundColor() const;
    std::optional<StatusItem::Color> getBackgroundColor() const;
    std::optional<StatusItem::Color> getBorderColor() const;
    [[nodiscard]] std::optional<std::chrono::milliseconds> getInterval() const;
    [[nodiscard]] bool hasSeparatorAfter() const;

  private:
    std::string mText;
    std::string mName;
    std::string mInstance;
    std::string mScript;
    std::optional<StatusItem::Color> mForegroundColor;
    std::optional<StatusItem::Color> mBackgroundColor;
    std::optional<StatusItem::Color> mBorderColor;
    bool mSeparatorAfter;
    std::optional<std::chrono::milliseconds> mInterval;
    mutable std::mutex mMutex;
};

#endif
