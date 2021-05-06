#ifndef STATUSITEM_H
#define STATUSITEM_H

#include <string>

#include "sstatus/ShellInterpreter.h"

class StatusItem {
  public:
    StatusItem(std::string name,
               std::string instance,
               std::string script,
               std::string foregroundColor,
               std::string backgroundColor,
               std::string borderColor,
               bool separatorAfter,
               long interval);

    std::string getName();
    std::string getInstance();
    std::string getScript();
    std::string getForegroundColor();
    std::string getBackgroundColor();
    std::string getBorderColor();
    [[nodiscard]] long getInterval() const;
    [[nodiscard]] bool hasSeparatorAfter() const;

  private:
    std::string mName;
    std::string mInstance;
    std::string mScript;
    std::string mForegroundColor;
    std::string mBackgroundColor;
    std::string mBorderColor;
    bool mSeparatorAfter;
    long mInterval;  // Number of milliseconds between refreshing this StatusItem
};

#endif
