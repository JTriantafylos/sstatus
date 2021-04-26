#include "sstatus/Control.h"

void Control::launch() {
    mConfigParser.init(getConfigFilePath());
    mRefreshTime = mConfigParser.loadRefreshTime();
    mItems = mConfigParser.loadStatusItems();
    mStreamWriter.initJSONStream();

    while(true) {
        auto generateStatusStart = std::chrono::high_resolution_clock::now();
        generateStatus();
        auto generateStatusEnd = std::chrono::high_resolution_clock::now();

        auto generateStatusDuration = std::chrono::duration_cast<std::chrono::milliseconds>(generateStatusEnd - generateStatusStart).count();
        // TODO: Handle condition where generateStatus takes longer than the refresh interval
        auto sleepDuration = ((mRefreshTime - generateStatusDuration) > 0) ? (mRefreshTime - generateStatusDuration) : 0;
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepDuration));
    }
}

void Control::generateStatus() {
    mStreamWriter.beginStatusItemArray();
    for(std::vector<StatusItem*>::iterator it = mItems.begin(); it != mItems.end(); ++it) {
        bool lastItem = false;
        if(it + 1 == mItems.end())
            lastItem = true;
        StatusItem* item = *it;
        mStreamWriter.writeStatusItem(item->getJsonText(), lastItem);
    }
    mStreamWriter.endStatusItemArray();
}

/*
 * TODO: Add support for custom config file location.
 */
std::string Control::getConfigFilePath() {
    std::string configFilePath = "";

    if(getenv("XDG_CONFIG_HOME") != NULL) {
        configFilePath = getenv("XDG_CONFIG_HOME");
        configFilePath.append("/sstatus");
        configFilePath.append("/config.toml");
    } else if(getenv("HOME") != NULL) {
        configFilePath = getenv("HOME");
        configFilePath.append("/.config");
        configFilePath.append("/sstatus");
        configFilePath.append("/config.toml");
    }

    return configFilePath;
}
