#ifndef STATUSITEMTHREAD_H
#define STATUSITEMTHREAD_H

#include <condition_variable>
#include <functional>
#include <mutex>
#include <thread>

#include "blockingconcurrentqueue.h"

#include "sstatus/StatusItem.h"

class StatusItemThread {
  public:
    explicit StatusItemThread(
        StatusItem* statusItem,
        int id,
        moodycamel::BlockingConcurrentQueue<std::pair<std::string, int>>* queue);

  private:
    void run(StatusItem* statusItem,
             int id,
             moodycamel::BlockingConcurrentQueue<std::pair<std::string, int>>* queue);

    std::thread mThread;
};

#endif
