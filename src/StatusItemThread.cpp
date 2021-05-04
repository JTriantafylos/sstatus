#include "sstatus/StatusItemThread.h"

StatusItemThread::StatusItemThread(
    StatusItem* statusItem,
    int id,
    moodycamel::BlockingConcurrentQueue<std::pair<std::string, int>>* queue) {
    mThread = std::thread([&, statusItem, id, queue]() { run(statusItem, id, queue); });
}

void StatusItemThread::run(
    StatusItem* statusItem,
    int id,
    moodycamel::BlockingConcurrentQueue<std::pair<std::string, int>>* queue) {
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
        auto runDuration =
            std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
        auto sleepDuration = statusItem->getInterval() - runDuration.count();
        // TODO: Look into one thread sleeping blocking the others
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepDuration));
    }
}

std::string StatusItemThread::generateStatusItemJsonString(StatusItem& item) {
    std::string script = item.getScript();
    std::string fullText = ShellInterpreter::interpret(script);
    return generateStatusItemJsonString(fullText, item);
}

std::string StatusItemThread::generateStatusItemJsonString(const std::string& fullText,
                                                           StatusItem& item) {
    std::string jsonString;

    jsonString.append("{");

    if (!fullText.empty()) {
        jsonString.append("\"full_text\": ");
        jsonString.append("\"");
        jsonString.append(fullText);
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
