#include "sstatus/ShellInterpreter.h"

using namespace std;

string ShellInterpreter::interpret(string mScript) {
    array<char, 256> buffer;
    string result;

    FILE* pipeO = popen(mScript.c_str(), "r");
    if (pipeO == nullptr) {
        result = "Command Failed!";
        return result;
    }
    while (fgets(buffer.data(), buffer.size(), pipeO) != nullptr) {
        result += buffer.data();
    }
    // Remove any newline characters from the line
    result = regex_replace(result, regex("\n+"), "");

    int pipeC = pclose(pipeO);
    if(pipeC != 0)
        result = "Command failed!";

    return result;
}
