#ifndef SHELLINTERPRETER_H
#define SHELLINTERPRETER_H

#include <array>
#include <stdexcept>
#include <string>

class ShellInterpreter {
  public:
    static std::string interpret(const std::string& script);
};

#endif
