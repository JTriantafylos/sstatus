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
    std::vector<StatusItem> loadStatusItemsFromConfig(const std::string& configFilePath) {
        toml::table config;
        std::vector<StatusItem> items;

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

            std::string name = orderItem->as_string()->get();
            if (!config[name]) {
                std::string errorMessage("Non-existent status item '" + name + "' in order array!");
                throw std::runtime_error(errorMessage);
            }

            auto table = config[name];

            std::string instance = std::string(name + "_" + std::to_string(i));
            std::string script = table["Script"].value_or("");
            std::optional<StatusItem::Color> foregroundColor = table["ForegroundColor"]
                                                                    .value<std::string>()
                                                                    .transform(StatusItem::Color::fromHexString);
            std::optional<StatusItem::Color> backgroundColor = table["BackgroundColor"]
                                                                    .value<std::string>()
                                                                    .transform(StatusItem::Color::fromHexString);
            std::optional<StatusItem::Color> borderColor = table["BorderColor"]
                                                                .value<std::string>()
                                                                .transform(StatusItem::Color::fromHexString);
            bool separatorAfter = table["SeparatorAfter"].value_or(true);
            long interval = table["Interval"].value_or(-1);

            items.emplace_back(name,
                               instance,
                               script,
                               foregroundColor,
                               backgroundColor,
                               borderColor,
                               separatorAfter,
                               interval);
        }
        return items;
    }
}
