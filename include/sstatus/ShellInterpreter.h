#ifndef SHELLINTERPRETER_H
#define SHELLINTERPRETER_H

#include <string>
#include <array>
#include <memory>
#include <regex>

class ShellInterpreter {
    public:
        std::string interpret(std::string);
};

#endif