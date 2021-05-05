#include "sstatus/Control.h"

Control::Control()
    : mStatusItemUpdateQueue(new moodycamel::BlockingConcurrentQueue<std::pair<std::string, int>>) {
}

// TODO: Find a way to terminate all StatusItemThreads on destruction of Control object
Control::~Control() = default;

void Control::launch() {
    StreamWriter::initJSONStream();

    try {
        mStatusItems = ConfigParser::loadStatusItemsFromConfig(getConfigFilePath());
    } catch (std::exception& err) {
        StreamWriter::writeError(err.what());
        // TODO: Find a cleaner way to pause execution after an error
        std::this_thread::sleep_for(std::chrono::hours::max());
    }

    int idCount = 0;
    for (const std::shared_ptr<StatusItem>& statusItem : mStatusItems) {
        mStatusItemThreads.emplace_back(idCount++, statusItem, mStatusItemUpdateQueue);
        mStatusItemTextArray.emplace_back("");
    }

    run();
}

[[noreturn]] void Control::run() {
    while (true) {
        std::pair<std::string, int> updatedItem;

        mStatusItemUpdateQueue->wait_dequeue(updatedItem);
        mStatusItemTextArray.at(updatedItem.second) = updatedItem.first;

        while (mStatusItemUpdateQueue->try_dequeue(updatedItem)) {
            mStatusItemTextArray.at(updatedItem.second) = updatedItem.first;
        }
        generateStatus();
    }
}

void Control::generateStatus() {
    StreamWriter::beginStatusItemArray();
    bool firstItem = true;
    for (const std::string& text : mStatusItemTextArray) {
        if (!text.empty()) {
            StreamWriter::writeStatusItem(text, firstItem);
            firstItem = false;
        }
    }
    StreamWriter::endStatusItemArray();
}

/*
 * TODO: Add support for custom config file location.
 */
std::string Control::getConfigFilePath() {
    std::string configFilePath;

    if (getenv("XDG_CONFIG_HOME") != nullptr) {
        configFilePath = getenv("XDG_CONFIG_HOME");
        configFilePath.append("/sstatus");
        configFilePath.append("/config.toml");
    } else if (getenv("HOME") != nullptr) {
        configFilePath = getenv("HOME");
        configFilePath.append("/.config");
        configFilePath.append("/sstatus");
        configFilePath.append("/config.toml");
    }

    return configFilePath;
}
