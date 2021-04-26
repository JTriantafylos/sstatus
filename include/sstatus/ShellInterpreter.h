#ifndef SHELLINTERPRETER_H
#define SHELLINTERPRETER_H

#include <string>
#include <array>
#include <memory>

class ShellInterpreter {
    public:
        static std::string interpret(const std::string& script);
};

#endif
