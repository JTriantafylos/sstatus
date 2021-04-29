#include "sstatus/StatusItemThread.h"

StatusItemThread::StatusItemThread(
    StatusItem* statusItem,
    int id,
    moodycamel::BlockingConcurrentQueue<std::pair<std::string, int>>* queue) {
    mThread = std::thread([&, statusItem, id, queue]() { run(statusItem, id, queue); });
}

[[noreturn]] void StatusItemThread::run(
    StatusItem* statusItem,
    int id,
    moodycamel::BlockingConcurrentQueue<std::pair<std::string, int>>* queue) {
    std::string lastJsonText;

    while (true) {
        //  TODO: Account for the time that this call takes
        std::string newJsonText = statusItem->getJsonText();
        if (newJsonText != lastJsonText) {
            lastJsonText = newJsonText;
            queue->enqueue(std::pair<std::string, int>(lastJsonText, id));
        }

        // TODO: Get proper timout time from status item
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}
