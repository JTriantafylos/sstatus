#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <algorithm>
#include <fstream>  // Required for toml++ to read from file
#include <string>
#include <vector>

#include "sstatus/ShellInterpreter.h"
#include "sstatus/StatusItem.h"

#include <toml++/toml.h>

class ConfigParser {
  public:
    static std::vector<std::shared_ptr<StatusItem>> loadStatusItemsFromConfig(
        const std::string& configFilePath);

  private:
    static bool isValidStatusItem(toml::node_view<toml::node> node);
};

#endif
