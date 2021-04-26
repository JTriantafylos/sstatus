#include "sstatus/ShellInterpreter.h"

std::string ShellInterpreter::interpret(std::string mScript) {
    std::array<char, 256> buffer;
    std::string result;

    FILE* pipeO = popen(mScript.c_str(), "r");
    if (pipeO == nullptr) {
        result = "Command Failed!";
        return result;
    }
    while (fgets(buffer.data(), buffer.size(), pipeO) != nullptr) {
        result += buffer.data();
    }

    int pipeC = pclose(pipeO);
    if(pipeC != 0)
        result = "Command failed!";

    return result;
}
