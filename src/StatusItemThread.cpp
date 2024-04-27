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

StatusItemThread::StatusItemThread(int id,
                                   StatusItem& statusItem,
                                   mpmcplusplus::Queue<std::pair<std::string, int>>& queue)
    : mStatusItem(statusItem),
    std::thread([id, &statusItem, &queue]() { run(id, statusItem, queue); }) {}

void StatusItemThread::run(int id,
                           StatusItem& statusItem,
                           mpmcplusplus::Queue<std::pair<std::string, int>>& queue) {
    std::string loadingText = "Loading...";
    queue.push(std::pair<std::string, int>(loadingText, id));

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
            queue.push(std::pair<std::string, int>(text, id));
            statusItem.setText(text);
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
