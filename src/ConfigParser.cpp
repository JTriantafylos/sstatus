#include "sstatus/ConfigParser.h"

using namespace std;

/*
 * TODO: Warn user that config file is broken as opposed to crashing out.
 */
vector<StatusItem*> ConfigParser::loadConfig(string configFile) {
    vector<StatusItem*> items;

    toml::table parsedConfig;
    try {
        parsedConfig = toml::parse_file(configFile);
    } catch(string msg) {
        cout << msg << endl;
    }

    toml::node_view<toml::node> statusItemsTable = parsedConfig["StatusItems"];
    int statusItemsTableSize = statusItemsTable.as_array()->size();

    for(int i = 0; i < statusItemsTableSize; ++i) {
        auto currItem = statusItemsTable[i].as_table();
        StatusItem* mItem = new StatusItem;

        /*
         * TODO: Implement other status item fields.
         */
        mItem->setFullText(currItem->get_as<string>("FullText")->get());

        items.push_back(mItem);
    }

    return items;
}
