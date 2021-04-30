#include "sstatus/Control.h"

[[noreturn]] void Control::launch() {
    std::vector<StatusItem*> statusItems;
    try {
        statusItems = ConfigParser::loadStatusItemsFromConfig(getConfigFilePath());
    } catch (std::exception& err) {
        StreamWriter::initJSONStream();
        StreamWriter::writeError(err.what());
        std::this_thread::sleep_for(std::chrono::hours::max());
    }

    int idCount = 0;
    for (StatusItem* statusItem : statusItems) {
        mStatusItemThreads.emplace_back(statusItem, idCount++, &mStatusItemUpdateQueue);
        mStatusItemTextArray.emplace_back("");
    }

    StreamWriter::initJSONStream();
    while (true) {
        std::pair<std::string, int> updatedItem;

        while (mStatusItemUpdateQueue.try_dequeue(updatedItem)) {
            mStatusItemTextArray.at(updatedItem.second) = updatedItem.first;
        }
        generateStatus();

        mStatusItemUpdateQueue.wait_dequeue(updatedItem);
        mStatusItemTextArray.at(updatedItem.second) = updatedItem.first;
    }
}

void Control::generateStatus() {
    StreamWriter::beginStatusItemArray();
    bool firstItem = true;
    for (const std::string& text: mStatusItemTextArray) {
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