#include "sstatus/ConfigParser.h"

void ConfigParser::init(const std::string& configFile) {
    /*
     * TODO: Handle missing config files
     */
    try {
        mConfig = toml::parse_file(configFile);
    } catch(toml::parse_error& err) {
        // TODO: Handle potential error
    }
}

int ConfigParser::loadRefreshTime() {
    auto generalSettingsTable = mConfig["General"];
    return generalSettingsTable.as_table()->get_as<int64_t>("RefreshTime")->get(); // TODO: Handle conversion of int64_t to int
}

std::vector<StatusItem> ConfigParser::loadStatusItems() {
    std::vector<StatusItem> items;

    auto statusItemsTableArray = mConfig["StatusItems"];
    std::size_t statusItemsTableSize = statusItemsTableArray.as_array()->size();

    for(int i = 0; i < statusItemsTableSize; ++i) {
        auto currItem = statusItemsTableArray[i].as_table();
        StatusItem mItem = StatusItem();

        /*
         * TODO: Implement other status item fields
         * TODO: Implement error handling for missing status item fields
         */
        mItem.setForegroundColor(currItem->get_as<std::string>("ForegroundColor")->get());
        mItem.setBackgroundColor(currItem->get_as<std::string>("BackgroundColor")->get());
        mItem.setBorderColor(currItem->get_as<std::string>("BorderColor")->get());
        mItem.setScript(currItem->get_as<std::string>("Script")->get());
        mItem.setInterval((currItem->get_as<int64_t>("Interval")->get())); // TODO: Handle conversion of int64_t to int

        items.push_back(mItem);
    }
    return items;
}
