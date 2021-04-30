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

    std::string getJsonText();

    std::string getFullText();

    std::string getForegroundColor();

    std::string getBackgroundColor();

    std::string getBorderColor();

    [[nodiscard]] long getInterval() const;

    [[nodiscard]] bool hasSeparatorAfter() const;

  protected:
    std::string fullText;

    std::string foregroundColor;
    std::string backgroundColor;
    std::string borderColor;

    int borderWidthTop = 1;
    int borderWidthBottom = 1;
    int borderWidthLeft = 1;
    int borderWidthRight = 1;

    int minimumWidth = -1;

    std::string alignment = "left";

    std::string name;
    std::string instance;

    bool urgent = false;

    bool separatorAfter = true;
    int separatorBlockWidth = 9;

    std::string script;

    long interval;            // Number of milliseconds between refreshing this StatusItem
    bool persistent = false;  // Whether or not the script has been run for the
                              // first time when interval is set to -1
  private:
    class StatusItemJsonFormatter {
      public:
        static std::string statusItemToJson(StatusItem&);
    };
};

#endif
