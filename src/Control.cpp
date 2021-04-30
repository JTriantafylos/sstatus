#include "sstatus/Control.h"

[[noreturn]] void Control::launch() {
    mConfigParser.init(getConfigFilePath());

    int idCount = 0;
    for (StatusItem* statusItem : mConfigParser.loadStatusItems()) {
        mStatusItemThreads.emplace_back(statusItem, idCount, &mStatusItemUpdateQueue);
        mStatusItemTextArray.emplace_back("");
        idCount++;
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
    for (auto it = mStatusItemTextArray.begin(); it != mStatusItemTextArray.end(); ++it) {
        bool lastItem = false;
        if (it + 1 == mStatusItemTextArray.end())
            lastItem = true;
        std::string text = *it;
        if (!text.empty()) {
            StreamWriter::writeStatusItem(text, lastItem);
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