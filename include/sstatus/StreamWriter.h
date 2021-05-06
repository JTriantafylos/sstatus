#ifndef STREAMWRITER_H
#define STREAMWRITER_H

#include <iostream>
#include <regex>
#include <string>

#include "sstatus/StatusItem.h"

namespace StreamWriter {
    void writeError(const std::string& errorText);
    void writeStatusItem(const std::string& jsonText, bool firstItem);
    void beginStatusItemArray();
    void endStatusItemArray();
    void initJSONStream();
}

#endif
