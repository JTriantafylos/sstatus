#include "sstatus/Control.h"

using namespace std;

void Control::launch() {
    mStreamWriter.initJSONStream();
    initItems();

    while(true) {
        generateStatus();
        this_thread::sleep_for(chrono::seconds(1));
    }
}

void Control::generateStatus() {
    mStreamWriter.beginStatusItemArray();
    for(vector<StatusItem*>::iterator it = mItems.begin(); it != mItems.end(); ++it) {
        bool lastItem = false;
        if(it + 1 == mItems.end())
            lastItem = true;
        StatusItem* item = *it;
        mStreamWriter.writeStatusItem(item->getJsonText(), lastItem);
    }
    mStreamWriter.endStatusItemArray();
}

void Control::initItems() {
    mItems = mConfigParser.loadConfig(getConfigFilePath());
}

/*
 * TODO: Add support for custom config file location.
 */
string Control::getConfigFilePath() {
    string configFilePath = "";

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
