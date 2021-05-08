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

StatusItemThread::StatusItemThread(
    int id,
    const std::shared_ptr<StatusItem>& statusItem,
    const std::shared_ptr<moodycamel::BlockingConcurrentQueue<std::pair<std::string, int>>>& queue)
    : std::thread([statusItem, id, queue]() { run(id, statusItem, queue); }) {}

void StatusItemThread::run(
    int id,
    const std::shared_ptr<StatusItem>& statusItem,
    const std::shared_ptr<moodycamel::BlockingConcurrentQueue<std::pair<std::string, int>>>& queue) {
    std::string lastJsonText;

    std::string loadingJsonText = generateStatusItemJsonString("Loading...", *statusItem);
    queue->enqueue(std::pair<std::string, int>(loadingJsonText, id));

    while (true) {
        auto startTime = std::chrono::high_resolution_clock::now();

        std::string newJsonText = generateStatusItemJsonString(*statusItem);
        if (newJsonText != lastJsonText) {
            lastJsonText = newJsonText;
            queue->enqueue(std::pair<std::string, int>(lastJsonText, id));
        }

        if (statusItem->getInterval() == -1) {
            return;
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        auto runDuration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
        auto sleepDuration = statusItem->getInterval() - runDuration.count();
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepDuration));
    }
}

std::string StatusItemThread::generateStatusItemJsonString(StatusItem& item) {
    std::string script = item.getScript();
    std::string fullText;
    try {
        // TODO: Escape characters such as double quotes
        fullText = ShellInterpreter::interpret(script);
    } catch (std::exception& err) {
        fullText = err.what();
    }
    return generateStatusItemJsonString(fullText, item);
}

std::string StatusItemThread::generateStatusItemJsonString(const std::string& fullText, StatusItem& item) {
    std::string jsonString;

    jsonString.append("{");

    if (!fullText.empty()) {
        jsonString.append("\"full_text\": ");
        jsonString.append("\"");
        jsonString.append(fullText);
        jsonString.append("\"");
        jsonString.append(",");
    }

    std::string name = item.getName();
    if (!name.empty()) {
        jsonString.append("\"name\": ");
        jsonString.append("\"");
        jsonString.append(name);
        jsonString.append("\"");
        jsonString.append(",");
    }

    std::string instance = item.getInstance();
    if (!instance.empty()) {
        jsonString.append("\"instance\": ");
        jsonString.append("\"");
        jsonString.append(instance);
        jsonString.append("\"");
        jsonString.append(",");
    }

    std::string foregroundColor = item.getForegroundColor();
    if (!foregroundColor.empty()) {
        jsonString.append("\"color\": ");
        jsonString.append("\"");
        jsonString.append(foregroundColor);
        jsonString.append("\"");
        jsonString.append(",");
    }

    std::string backgroundColor = item.getBackgroundColor();
    if (!backgroundColor.empty()) {
        jsonString.append("\"background\": ");
        jsonString.append("\"");
        jsonString.append(backgroundColor);
        jsonString.append("\"");
        jsonString.append(",");
    }

    std::string borderColor = item.getBorderColor();
    if (!borderColor.empty()) {
        jsonString.append("\"border\": ");
        jsonString.append("\"");
        jsonString.append(borderColor);
        jsonString.append("\"");
        jsonString.append(",");
    }

    /*
     * TODO: Implement other StatusItem fields.
     */

    jsonString.append("\"separator\": ");
    jsonString.append(item.hasSeparatorAfter() ? "true" : "false");

    jsonString.append("}");

    return jsonString;
}
