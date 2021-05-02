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

    while (true) {
        auto startTime = std::chrono::high_resolution_clock::now();

        std::string newJsonText = statusItem->getJsonText();
        if (newJsonText != lastJsonText) {
            lastJsonText = newJsonText;
            queue->enqueue(std::pair<std::string, int>(lastJsonText, id));
        }

        if(statusItem->getInterval() == -1) {
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
