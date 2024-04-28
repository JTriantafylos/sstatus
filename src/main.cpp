/*
 * main.cpp - Program entry point
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

#include <getopt.h>
#include <filesystem>
#include <format>
#include <iostream>

#include "sstatus/Control.h"
#include "sstatus/streamwriters/SwaybarStreamWriter.h"

namespace {
std::string getDefaultConfigFilePath() {
    std::string configFilePath;

    if (getenv("XDG_CONFIG_HOME") != nullptr) {
        configFilePath = std::format("{}/sstatus/config.toml", getenv("XDG_CONFIG_HOME"));
    } else if (getenv("HOME") != nullptr) {
        configFilePath = std::format("{}/.config/sstatus/config.toml", getenv("HOME"));
    }

    return configFilePath;
}
}

int main(int argc, char* argv[]) {
    SwaybarStreamWriter streamWriter;
    Control control(streamWriter);

    std::string configFilePath = getDefaultConfigFilePath();

    int opt = 0;
    while ((opt = getopt(argc, argv, "c:")) != -1) {
        switch (opt) {
            case 'c':
                if (!std::filesystem::exists(optarg)) {
                    std::cerr << argv[0] << ": Specified configuration file does not exist" << '\n';
                    exit(EXIT_FAILURE);
                }
                configFilePath = optarg;
                break;
            default:
                exit(EXIT_FAILURE);
        }
    }

    control.launch(configFilePath);
}
