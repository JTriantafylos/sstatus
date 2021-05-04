#include "sstatus/ConfigParser.h"

std::vector<std::shared_ptr<StatusItem>> ConfigParser::loadStatusItemsFromConfig(
    const std::string& configFilePath) {
    toml::table config;
    std::vector<std::shared_ptr<StatusItem>> items;

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
        std::shared_ptr<StatusItem> item;
        if (isValidStatusItem(statusItemsArray[i])) {
            std::string s = statusItemsArray[i]["Script"].value_or("");
            std::string fg = statusItemsArray[i]["ForegroundColor"].value_or("");
            std::string bg = statusItemsArray[i]["BackgroundColor"].value_or("");
            std::string bc = statusItemsArray[i]["BorderColor"].value_or("");
            long interval = statusItemsArray[i]["Interval"].value_or(-1);
            item = std::make_shared<StatusItem>(s, fg, bg, bc, interval);
        } else {
            item = std::make_shared<StatusItem>("echo \"Malformed status item configuration!\"",
                                                "#ff0000", "", "", -1);
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
