#include "sstatus/ShellInterpreter.h"
namespace ShellInterpreter {
    std::string interpret(const std::string& script) {
        std::array<char, 128> buffer{};
        std::string result;

        FILE* pipe = popen(script.c_str(), "r");
        if (pipe == nullptr) {
            throw std::runtime_error("Shell interpretation failed!");
        }

        while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
            result.append(buffer.data());
        }

        if (pclose(pipe) != 0) {
            throw std::runtime_error("Shell interpretation failed!");
        }

        return result;
    }
}