#ifndef STATUSITEMTHREAD_H
#define STATUSITEMTHREAD_H

#include <condition_variable>
#include <functional>
#include <mutex>
#include <thread>

#include "blockingconcurrentqueue.h"

#include "sstatus/StatusItem.h"

class StatusItemThread : public std::thread {
  public:
    explicit StatusItemThread(
        StatusItem* statusItem,
        int id,
        moodycamel::BlockingConcurrentQueue<std::pair<std::string, int>>* queue);

  private:
    static void run(int id,
                    StatusItem* statusItem,
                    moodycamel::BlockingConcurrentQueue<std::pair<std::string, int>>* queue);
    static std::string generateStatusItemJsonString(const std::string& fullText, StatusItem& item);
    static std::string generateStatusItemJsonString(StatusItem& item);
};

#endif
