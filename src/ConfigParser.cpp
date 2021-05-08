/*
 * ConfigParser.cpp - Configuration file parser
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

#include "sstatus/ConfigParser.h"

namespace ConfigParser {
    namespace {
        // TODO: If invalid, specify which field(s) is invalid
        bool isValidStatusItem(const toml::table& table) {
            if (table["Script"].is_string() && table["ForegroundColor"].is_string() &&
                table["BackgroundColor"].is_string() && table["BorderColor"].is_string() &&
                table["SeparatorAfter"].is_boolean() && table["Interval"].is_number()) {
                return true;
            } else {
                return false;
            }
        }
    }

    std::vector<std::shared_ptr<StatusItem>> loadStatusItemsFromConfig(const std::string& configFilePath) {
        toml::table config;
        std::vector<std::shared_ptr<StatusItem>> items;

        try {
            config = toml::parse_file(configFilePath);
        } catch (toml::parse_error& err) {
            throw err;
        }

        if (!config["Order"].is_array()) {
            throw std::runtime_error("Status item order array is not defined!");
        }

        toml::array* orderArray = config["Order"].as_array();
        for (int i = 0; i < orderArray->size(); ++i) {
            const toml::node* orderItem = orderArray->get(i);
            if (!orderItem->is_string()) {
                std::string errorMessage("Invalid status item in order array at position [" + std::to_string(i) + "]!");
                throw std::runtime_error(errorMessage);
            }

            std::string statusItemName = orderItem->as_string()->get();
            if (!config[statusItemName]) {
                std::string errorMessage("Non-existent status item '" + statusItemName + "' in order array!");
                throw std::runtime_error(errorMessage);
            }

            toml::table* table = config[statusItemName].as_table();
            if (!isValidStatusItem(*table)) {
                std::string errorMessage("Malformed configuration for status item: '" + statusItemName + "'!");
                throw std::runtime_error(errorMessage);
            }

            // TODO: Implement other status item fields
            std::shared_ptr<StatusItem> item;

            std::string in = std::string(statusItemName + "_" + std::to_string(i));
            std::string s = table->get("Script")->value_or("");
            std::string fg = table->get("ForegroundColor")->value_or("");
            std::string bg = table->get("BackgroundColor")->value_or("");
            std::string bc = table->get("BorderColor")->value_or("");
            bool sep = table->get("SeparatorAfter")->value_or(true);
            long interval = table->get("Interval")->value_or(-1);

            item = std::make_shared<StatusItem>(statusItemName, in, s, fg, bg, bc, sep, interval);
            items.push_back(item);
        }
        return items;
    }
}