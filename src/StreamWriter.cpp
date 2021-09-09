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

#include "sstatus/StreamWriter.h"

namespace StreamWriter {
    void writeError(const std::string& errorText) {
        beginStatusItemArray();

        std::string errorJson;
        errorJson.append("{");
        errorJson.append("\"full_text\": ");
        errorJson.append("\"");
        errorJson.append("sstatus: ");
        errorJson.append(removeNewlines(errorText));
        errorJson.append("\"");
        errorJson.append(",");
        errorJson.append("\"color\": ");
        errorJson.append("\"");
        errorJson.append("#ff0000");
        errorJson.append("\"");
        errorJson.append("}");

        std::cout << errorJson;

        endStatusItemArray();

        std::cout << std::flush;
    }

    void writeStatusItem(const std::string& jsonText, bool firstItem) {
        if (!firstItem)
            std::cout << ",";

        std::cout << removeNewlines(jsonText);
        std::cout << std::flush;
    }

    void initJSONStream() {
        std::cout << R"({"version": 1}[)";
        std::cout << std::flush;
    }

    void beginStatusItemArray() {
        std::cout << "[";
        std::cout << std::flush;
    }

    void endStatusItemArray() {
        std::cout << "],";
        std::cout << std::flush;
    }

    std::string removeNewlines(const std::string& stringIn) { return regex_replace(stringIn, std::regex("\n+"), ""); }
}