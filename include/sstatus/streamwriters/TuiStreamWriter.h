/*
 * StreamWriter.h - Stdout stream writer header
 * Copyright (C) 2024 James Triantafylos
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

#ifndef TUISTREAMWRITER_H
#define TUISTREAMWRITER_H

#include <ftxui/screen/screen.hpp>
#include <string>

#include "sstatus/StreamWriter.h"

class TuiStreamWriter : public StreamWriter {
  public:
    TuiStreamWriter();
    void writeError(const std::string& errorText) override;
    void writeStatusItems(const std::vector<StatusItem>& statusItems) override;

  private:
    ftxui::Screen mScreen;
};

#endif
