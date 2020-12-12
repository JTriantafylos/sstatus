#include "sstatus/ConfigParser.h"

using namespace std;

/*
 * TODO: Warn user that config file is broken as opposed to crashing out.
 */
void ConfigParser::init(string configFile) {
    /*
     * TODO: Handle missing or invalid config files
     */
    try {
        mConfig = toml::parse_file(configFile);
    } catch(toml::parse_error& err) {
        // TODO: Handle error
        mConfig = toml::table();
    }
}

int ConfigParser::loadRefreshTime() {
    auto generalSettingsTable = mConfig["General"];
    return generalSettingsTable.as_table()->get_as<int64_t>("RefreshTime")->get(); // TODO: Handle conversion of int64_t to int
}

vector<StatusItem*> ConfigParser::loadStatusItems() {
    vector<StatusItem*> items;

    auto statusItemsTableArray = mConfig["StatusItems"];
    int statusItemsTableSize = statusItemsTableArray.as_array()->size();

    for(int i = 0; i < statusItemsTableSize; ++i) {
        auto currItem = statusItemsTableArray[i].as_table();
        StatusItem* mItem = new StatusItem;

        /*
         * TODO: Implement other status item fields
         * TODO: Implement error handling for missing status item fields
         */
        mItem->setScript(currItem->get_as<string>("Script")->get());
        mItem->setInterval((currItem->get_as<int64_t>("Interval")->get())); // TODO: Handle conversion of int64_t to int

        items.push_back(mItem);
    }
    return items;
}
