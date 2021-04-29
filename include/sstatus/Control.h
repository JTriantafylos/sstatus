#ifndef CONTROL_H
#define CONTROL_H

#include <chrono>
#include <cstdlib>
#include <string>
#include <thread>
#include <vector>

#include "blockingconcurrentqueue.h"

#include "sstatus/ConfigParser.h"
#include "sstatus/StatusItem.h"
#include "sstatus/StatusItemThread.h"
#include "sstatus/StreamWriter.h"

class Control {
  public:
    [[noreturn]] void launch();

  private:
    void generateStatus();
    static std::string getConfigFilePath();

    std::vector<std::shared_ptr<StatusItem>> mStatusItems;
    std::vector<StatusItemThread> mStatusItemThreads;
    std::vector<std::string> mStatusItemTextArray;
    ConfigParser mConfigParser;
    moodycamel::BlockingConcurrentQueue<std::pair<std::string, int>> mStatusItemUpdateQueue;
};

#endif
