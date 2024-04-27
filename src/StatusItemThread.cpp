/*
 * StatusItemThread.cpp - Status item specific thread
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

#include "sstatus/StatusItemThread.h"

#include "sstatus/ShellInterpreter.h"

namespace {
void modifyStatusItemText(StatusItem& statusItem,
                          const std::string text,
                          std::atomic_flag& notifyFlag) {
    statusItem.setText(text);
    notifyFlag.test_and_set();
    notifyFlag.notify_all();
}
}

StatusItemThread::StatusItemThread(int id,
                                   StatusItem& statusItem,
                                   std::atomic_flag& notifyFlag)
: std::thread([id, &statusItem, &notifyFlag]() { run(id, statusItem, notifyFlag); }) {}

void StatusItemThread::run(int id,
                           StatusItem& statusItem,
                           std::atomic_flag& notifyFlag) {
    modifyStatusItemText(statusItem, "Loading...", notifyFlag);

    std::string lastText;
    while (true) {
        auto startTime = std::chrono::high_resolution_clock::now();

        std::string text;
        try {
            text = ShellInterpreter::interpret(statusItem.getScript());
        } catch (std::exception& err) {
            text = err.what();
        }

        if (text != lastText) {
            lastText = text;
            modifyStatusItemText(statusItem, text, notifyFlag);
        }

        if (statusItem.getInterval() == -1) {
            return;
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        auto runDuration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
        auto sleepDuration = statusItem.getInterval() - runDuration.count();
        if (sleepDuration > 0)
            std::this_thread::sleep_for(std::chrono::milliseconds(sleepDuration));
    }
}
