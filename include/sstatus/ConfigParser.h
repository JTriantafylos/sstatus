#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <algorithm>
#include <fstream>  // Required for toml++ to read from file
#include <string>
#include <vector>

#include "sstatus/ShellInterpreter.h"
#include "sstatus/StatusItem.h"

#include <toml++/toml.h>

namespace ConfigParser {
    std::vector<std::shared_ptr<StatusItem>> loadStatusItemsFromConfig(const std::string& configFilePath);
}

#endif
