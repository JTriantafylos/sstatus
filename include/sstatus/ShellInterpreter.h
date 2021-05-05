#ifndef SHELLINTERPRETER_H
#define SHELLINTERPRETER_H

#include <array>
#include <stdexcept>
#include <string>

// TODO: Consider changing this from a class to a namespace
class ShellInterpreter {
  public:
    static std::string interpret(const std::string& script);
};

#endif
