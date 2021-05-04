#ifndef STATUSITEM_H
#define STATUSITEM_H

#include <string>

#include "sstatus/ShellInterpreter.h"

class StatusItem {
  public:
    StatusItem(std::string  s,
               std::string  fg,
               std::string  bg,
               std::string  bc,
               long i);

    std::string getScript();
    std::string getForegroundColor();
    std::string getBackgroundColor();
    std::string getBorderColor();
    [[nodiscard]] long getInterval() const;
    [[nodiscard]] bool hasSeparatorAfter() const;

  private:
    std::string script;
    std::string foregroundColor;
    std::string backgroundColor;
    std::string borderColor;
    bool separatorAfter = true;
    long interval; // Number of milliseconds between refreshing this StatusItem
};

#endif
