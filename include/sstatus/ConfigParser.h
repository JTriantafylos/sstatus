#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <algorithm>
#include <fstream> // Required for toml++ to read from file
#include <string>
#include <vector>

#include "sstatus/ShellInterpreter.h"
#include "sstatus/StatusItem.h"

#include <toml++/toml.h>

class ConfigParser {
public:
  void init(const std::string &configFile);
  std::vector<StatusItem*> loadStatusItems();
  int loadRefreshTime();

private:
  toml::table mConfig;
};

#endif
