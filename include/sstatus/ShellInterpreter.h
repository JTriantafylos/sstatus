#ifndef SHELLINTERPRETER_H
#define SHELLINTERPRETER_H

#include <array>
#include <stdexcept>
#include <string>

namespace ShellInterpreter {
    std::string interpret(const std::string& script);
}

#endif
