/*
 * ConfigParser.h - Configuration file parser header
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

#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <algorithm>
#include <fstream>  // Required for toml++ to read from file
#include <string>
#include <vector>

#include "sstatus/ShellInterpreter.h"
#include "sstatus/StatusItem.h"

#include <toml++/toml.h>

namespace ConfigParser {
    std::vector<StatusItem> loadStatusItemsFromConfig(const std::string& configFilePath);
}

#endif
