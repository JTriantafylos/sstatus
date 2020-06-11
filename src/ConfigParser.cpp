#include "sstatus/ConfigParser.h"

using namespace std;

/*
 * TODO: Warn user that config file is broken as opposed to crashing out.
 */
vector<StatusItem*> ConfigParser::loadConfig(string configFile) {
    vector<StatusItem*> items;
    toml::table parsedConfig;

    /*
     * TODO: Handle missing or invalid config files
     */
    try {
        parsedConfig = toml::parse_file(configFile);
    } catch(toml::parse_error& err) {
        StatusItem* errItem = new StatusItem;

        string errText = "";
        errText.append(err.description());

        // Checks if the error occured as a specific point in the config
        if(err.source().begin.operator bool()) {
            errText.append(" at");
            errText.append(" line: " + to_string(err.source().begin.line));
            errText.append(" column: " + to_string(err.source().begin.column));
        }

        // Changes backslashes to forward slashes to avoid escape sequences
        replace(errText.begin(), errText.end(), '\\', '/');

        errItem->setFullText(errText);
        items.push_back(errItem);
        return items;
    }

    auto statusItemsTable = parsedConfig["StatusItems"];
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
