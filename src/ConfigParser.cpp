#include "sstatus/ConfigParser.h"

std::vector<std::shared_ptr<StatusItem>> ConfigParser::loadStatusItemsFromConfig(const std::string& configFilePath) {
    toml::table config;
    std::vector<std::shared_ptr<StatusItem>> items;

    try {
        config = toml::parse_file(configFilePath);
    } catch (toml::parse_error& err) {
        throw err;
    }

    // TODO: Implement a way for the order of the status items to be specified in the config file
    for (auto node : config) {
        if (toml::table* table = node.second.as_table()) {
            std::string name = node.first;

            // TODO: Implement other status item fields
            std::shared_ptr<StatusItem> item;
            if (isValidStatusItem(*table)) {
                std::string s = table->get("Script")->value_or("");
                std::string fg = table->get("ForegroundColor")->value_or("");
                std::string bg = table->get("BackgroundColor")->value_or("");
                std::string bc = table->get("BorderColor")->value_or("");
                long interval = table->get("Interval")->value_or(-1);
                item = std::make_shared<StatusItem>(s, fg, bg, bc, interval);
            } else {
                item = std::make_shared<StatusItem>("echo \"Malformed status item configuration!\"", "#ff0000", "", "",
                                                    -1);
            }
            items.push_back(item);
        }
    }
    return items;
}
bool ConfigParser::isValidStatusItem(const toml::table& table) {
    if (table["Script"] && table["ForegroundColor"] && table["BackgroundColor"] && table["BorderColor"] &&
        table["Interval"]) {
        return true;
    } else {
        return false;
    }
}
