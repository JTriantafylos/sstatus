#include "sstatus/ConfigParser.h"

std::vector<StatusItem*> ConfigParser::loadStatusItemsFromConfig(
    const std::string& configFilePath) {
    toml::table config;
    std::vector<StatusItem*> items;

    try {
        config = toml::parse_file(configFilePath);
    } catch (toml::parse_error& err) {
        throw err;
    }

    auto statusItemsArray = config["StatusItems"];
    std::size_t statusItemsTableSize = statusItemsArray.as_array()->size();

    for (int i = 0; i < statusItemsTableSize; ++i) {
        /*
         * TODO: Implement other status item fields
         */
        StatusItem* item;
        if (isValidStatusItem(statusItemsArray[i])) {
            std::string s = statusItemsArray[i]["Script"].value_or("");
            std::string fg = statusItemsArray[i]["ForegroundColor"].value_or("");
            std::string bg = statusItemsArray[i]["BackgroundColor"].value_or("");
            std::string bc = statusItemsArray[i]["BorderColor"].value_or("");
            long interval = statusItemsArray[i]["Interval"].value_or(-1);
            item = new StatusItem(s, fg, bg, bc, interval);
        } else {
            std::string s = "echo \"Malformed status item configuration!\"";
            std::string fg = "#ff0000";
            std::string bg;
            std::string bc;
            long interval = -1;
            item = new StatusItem(s, fg, bg, bc, interval);
        }
        items.push_back(item);
    }
    return items;
}
bool ConfigParser::isValidStatusItem(toml::node_view<toml::node> node) {
    if (node["Script"] && node["ForegroundColor"] && node["BackgroundColor"] &&
        node["BorderColor"] && node["Interval"]) {
        return true;
    } else {
        return false;
    }
}
