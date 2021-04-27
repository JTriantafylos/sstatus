#ifndef SHELLINTERPRETER_H
#define SHELLINTERPRETER_H

#include <array>
#include <memory>
#include <string>

class ShellInterpreter {
  public:
    static std::string interpret(const std::string& script);
};

#endif
