#ifndef STREAMWRITER_H
#define STREAMWRITER_H

#include <iostream>
#include <regex>
#include <string>

#include "sstatus/StatusItem.h"

// TODO: Consider changing this from a class to a namespace
class StreamWriter {
  public:
    static void writeError(const std::string&);
    static void writeStatusItem(const std::string&, bool);
    static void beginStatusItemArray();
    static void endStatusItemArray();
    static void initJSONStream();
};

#endif
