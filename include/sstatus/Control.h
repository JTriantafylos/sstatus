#ifndef CONTROL_H
#define CONTROL_H

#include <cstdlib>
#include <string>
#include <vector>

#include <chrono>
#include <thread>

#include "sstatus/ConfigParser.h"

#include "sstatus/StreamWriter.h"

#include "sstatus/StatusItem.h"

class Control {
  public:
    [[noreturn]] void launch();

  private:
    void generateStatus();
    static std::string getConfigFilePath();

    int mRefreshTime = 1000;
    std::vector<StatusItem> mItems;

    ConfigParser mConfigParser;
};

#endif
