/*
 * Control.h - Main program control header
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

#ifndef CONTROL_H
#define CONTROL_H

#include <chrono>
#include <cstdlib>
#include <string>
#include <thread>
#include <vector>

#include "mpmcplusplus/mpmcplusplus.h"

#include "sstatus/ConfigParser.h"
#include "sstatus/StatusItem.h"
#include "sstatus/StatusItemThread.h"
#include "sstatus/StreamWriter.h"

class Control {
  public:
    Control();
    ~Control();
    void launch(const std::string& configFilePath);

  private:
    [[noreturn]] void run();
    void generateStatus();

    std::vector<StatusItem> mStatusItems;
    std::vector<StatusItemThread> mStatusItemThreads;
    std::vector<std::string> mStatusItemTextArray;
    mpmcplusplus::Queue<std::pair<std::string, int>> mStatusItemUpdateQueue;
};

#endif
