/*
 * Control.cpp - Main program control
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

#include "sstatus/Control.h"
#include "sstatus/ConfigParser.h"

Control::Control(StreamWriter& streamWriter) : mStreamWriter(streamWriter)
{}

// TODO: Find a way to terminate all StatusItemThreads on destruction of Control object
Control::~Control() = default;

[[noreturn]] void Control::launch(const std::string& configFilePath) {
    try {
        mStatusItems = ConfigParser::loadStatusItemsFromConfig(configFilePath);

        int idCount = 0;
        for (StatusItem& statusItem : mStatusItems) {
            mStatusItemThreads.emplace_back(idCount++, statusItem, mNotifyFlag);
        }

        this->run();
    } catch (std::exception& err) {
        mStreamWriter.writeError(err.what());
        while (true) {
            pause();
        }
    }
}

[[noreturn]] void Control::run() {
    mStreamWriter.writePreamble();

    while (true) {
        while (!mNotifyFlag.test()) {
            mNotifyFlag.wait(false);
        }

        mStreamWriter.writeStatusItems(mStatusItems);

        mNotifyFlag.clear();
    }

    mStreamWriter.writeTrailer();
}
