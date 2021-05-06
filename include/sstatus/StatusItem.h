#ifndef STATUSITEM_H
#define STATUSITEM_H

#include <string>

#include "sstatus/ShellInterpreter.h"

class StatusItem {
  public:
    StatusItem(std::string script, std::string foregroundColor, std::string backgroundColor, std::string borderColor, long interval);

    std::string getScript();
    std::string getForegroundColor();
    std::string getBackgroundColor();
    std::string getBorderColor();
    [[nodiscard]] long getInterval() const;
    [[nodiscard]] bool hasSeparatorAfter() const;

  private:
    std::string mScript;
    std::string mForegroundColor;
    std::string mBackgroundColor;
    std::string mBorderColor;
    bool mSeparatorAfter = true;
    long mInterval;  // Number of milliseconds between refreshing this StatusItem
};

#endif
