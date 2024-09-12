/*
 * StreamWriter.cpp - Stdout stream writer
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

#include <iostream>
#include <regex>

#include "sstatus/streamwriters/SwaybarStreamWriter.h"

namespace {

    std::string removeNewlines(const std::string& stringIn) {
        return regex_replace(stringIn, std::regex("\n+"), "");
    }

    void writeJsonArrayBegin() {
        std::cout << "[" << std::flush;
    }

    void writeJsonArrayEnd() {
        std::cout << "]," << std::flush;
    }

    std::string generateStatusItemJsonString(const StatusItem& item) {
        std::string jsonString;

        jsonString.append("{");

        std::string text = item.getText();
        if (!text.empty()) {
            jsonString.append("\"full_text\": ");
            jsonString.append("\"");
            jsonString.append(text);
            jsonString.append("\"");
            jsonString.append(",");
        }

        std::string name = item.getName();
        if (!name.empty()) {
            jsonString.append("\"name\": ");
            jsonString.append("\"");
            jsonString.append(name);
            jsonString.append("\"");
            jsonString.append(",");
        }

        std::string instance = item.getInstance();
        if (!instance.empty()) {
            jsonString.append("\"instance\": ");
            jsonString.append("\"");
            jsonString.append(instance);
            jsonString.append("\"");
            jsonString.append(",");
        }

        std::optional<StatusItem::Color> foregroundColor = item.getForegroundColor();
        if (foregroundColor) {
            jsonString.append("\"color\": ");
            jsonString.append("\"");
            jsonString.append(foregroundColor->toHexString());
            jsonString.append("\"");
            jsonString.append(",");
        }

        std::optional<StatusItem::Color> backgroundColor = item.getBackgroundColor();
        if (backgroundColor) {
            jsonString.append("\"background\": ");
            jsonString.append("\"");
            jsonString.append(backgroundColor->toHexString());
            jsonString.append("\"");
            jsonString.append(",");
        }

        std::optional<StatusItem::Color> borderColor = item.getBorderColor();
        if (borderColor) {
            jsonString.append("\"border\": ");
            jsonString.append("\"");
            jsonString.append(borderColor->toHexString());
            jsonString.append("\"");
            jsonString.append(",");
        }

        jsonString.append("\"separator\": ");
        jsonString.append(item.hasSeparatorAfter() ? "true" : "false");

        jsonString.append("}");

        return jsonString;
    }

}  // namespace

void SwaybarStreamWriter::writeError(const std::string& errorText) {
    writeJsonArrayBegin();
    std::cout << R"({"full_text": "sstatus: )" << removeNewlines(errorText) << R"(","color": "#ff0000"})";
    writeJsonArrayEnd();

    std::cout << std::flush;
}
void SwaybarStreamWriter::writeStatusItems(const std::vector<StatusItem>& statusItems) {
    writeJsonArrayBegin();
    bool first = true;
    for (const StatusItem& statusItem : statusItems) {
        if (!first) {
            std::cout << ",";
        }
        first = false;

        std::cout << removeNewlines(generateStatusItemJsonString(statusItem)) << std::flush;
    }
    writeJsonArrayEnd();
}

void writeStatusItem(const std::string& jsonText, bool firstItem) {
    if (!firstItem)
        std::cout << ",";

    std::cout << removeNewlines(jsonText);
    std::cout << std::flush;
}

void SwaybarStreamWriter::writePreamble() {
    std::cout << R"({"version": 1})" << "\n" << "[" << std::flush;
}
