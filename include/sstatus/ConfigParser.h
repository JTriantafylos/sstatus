#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <vector>
#include <fstream> // Required for toml++ to read from file
#include <string>
#include <algorithm>
#include <iostream>

#include "sstatus/StatusItem.h"

#include "toml++/toml.h"

class ConfigParser {
    public:
        std::vector<StatusItem*> loadConfig(std::string);

    private:
        StatusItem* tomlToStatusItem(toml::table&);
        std::vector<StatusItem*> mItems;
};

#endif
