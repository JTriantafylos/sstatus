#include "sstatus/ShellInterpreter.h"

std::string ShellInterpreter::interpret(const std::string& script) {
    std::array<char, 256> buffer{};
    std::string result;

    FILE* pipeO = popen(script.c_str(), "r");
    if (pipeO == nullptr) {
        result = "Command Failed!";
        return result;
    }
    while (fgets(buffer.data(), buffer.size(), pipeO) != nullptr) {
        result += buffer.data();
    }

    int pipeC = pclose(pipeO);
    if (pipeC != 0)
        result = "Command failed!";

    return result;
}
