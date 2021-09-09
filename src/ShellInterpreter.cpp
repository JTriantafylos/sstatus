/*
 * ShellInterpreter.cpp - Shell script interpreter
 * Copyright (C) 2020-2021 James Triantafylos
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "sstatus/ShellInterpreter.h"
namespace ShellInterpreter {
    std::string interpret(const std::string& script) {
        std::array<char, 128> buffer{};
        std::string result;

        FILE* pipe = popen(script.c_str(), "r");
        if (pipe == nullptr) {
            throw std::runtime_error("Shell interpretation failed, could not open pipe!");
        }

        while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
            result.append(buffer.data());
        }

        int pipeCloseValue = pclose(pipe);
        if (pipeCloseValue != 0) {
            if (WIFEXITED(pipeCloseValue))
                throw std::runtime_error("Shell interpretation failed, command terminated with exit code: " +
                                         std::to_string(WEXITSTATUS(pipeCloseValue)));
            else
                throw std::runtime_error("Shell interpretation failed, command terminated abnormally!");
        }

        return result;
    }
}