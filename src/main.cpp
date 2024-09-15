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
#include <memory>
#include <stdexcept>

#include "sstatus/Control.h"
#include "sstatus/streamwriters/SwaybarStreamWriter.h"

#ifdef SSTATUS_FORMAT_TUI
#include "sstatus/streamwriters/TuiStreamWriter.h"
#endif

namespace {
    std::string getDefaultConfigFilePath() {
        char const* const xdgConfigHomeDir = getenv("XDG_CONFIG_HOME");
        if (xdgConfigHomeDir != nullptr) {
            return std::format("{}/sstatus/config.toml", xdgConfigHomeDir);
        }

        char const* const homeDir = getenv("HOME");
        if (homeDir != nullptr) {
            return std::format("{}/.config/sstatus/config.toml", homeDir);
        }

        return "/etc/sstatus/config.toml";
    }

    struct ProgramState {
        std::string configFilePath;
        std::unique_ptr<StreamWriter> streamWriter;
    };

    ProgramState parseOpts(const int argc, char* const* const argv) {
        ProgramState progState{.configFilePath = getDefaultConfigFilePath(),
                               .streamWriter = std::make_unique<SwaybarStreamWriter>()};
        int opt = 0;
        while ((opt = getopt(argc, argv, "c:f:")) != -1) {
            switch (opt) {
                case 'c': {
                    if (!std::filesystem::exists(optarg)) {
                        throw std::invalid_argument(std::format("Configuration file '{}' doesn't exist", optarg));
                    }
                    progState.configFilePath = optarg;
                    break;
                }
                case 'f': {
                    const std::string format(optarg);
                    if (format == "swaybar" || format == "i3bar") {
                        progState.streamWriter = std::make_unique<SwaybarStreamWriter>();
                    }
#ifdef SSTATUS_FORMAT_TUI
                    else if (format == "tui") {
                        progState.streamWriter = std::make_unique<TuiStreamWriter>();
                    }
#endif
                    else {
                        throw std::invalid_argument(std::format("Format type '{}' doesn't exist", format));
                    }
                    break;
                }
                default:
                    exit(EXIT_FAILURE);
            }
        }

        return progState;
    }
}  // namespace

int main(int argc, char* argv[]) {
    try {
        ProgramState progState = parseOpts(argc, argv);

        Control control(*progState.streamWriter);
        control.launch(progState.configFilePath);
    } catch (const std::exception& err) {
        std::cerr << argv[0] << ": " << err.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
