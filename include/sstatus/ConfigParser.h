#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <algorithm>
#include <fstream>  // Required for toml++ to read from file
#include <string>
#include <vector>

#include "sstatus/ShellInterpreter.h"
#include "sstatus/StatusItem.h"

#include <tomlplusplus/include/toml++/toml.h>

// TODO: Consider changing this from a class to a namespace
class ConfigParser {
  public:
    static std::vector<std::shared_ptr<StatusItem>> loadStatusItemsFromConfig(const std::string& configFilePath);

  private:
    static bool isValidStatusItem(const toml::table& table);
};

#endif
