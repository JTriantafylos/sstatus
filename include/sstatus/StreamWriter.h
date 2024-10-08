/*
 * StreamWriter.h - Stdout stream writer header
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

#ifndef STREAMWRITER_H
#define STREAMWRITER_H

#include <string>
#include <vector>
#include "sstatus/StatusItem.h"

class StreamWriter {
  public:
    virtual ~StreamWriter() = default;
    virtual void writeError(const std::string& errorText) = 0;
    virtual void writeStatusItems(const std::vector<StatusItem>& statusItems) = 0;
    virtual void writePreamble() {};
    virtual void writeTrailer() {};
};

#endif
