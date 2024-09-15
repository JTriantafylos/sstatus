/*
 * StreamWriter.cpp - TUI stream writer
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

#include "sstatus/streamwriters/TuiStreamWriter.h"

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/color.hpp>
#include <iostream>

TuiStreamWriter::TuiStreamWriter() : mScreen(ftxui::Screen::Create(ftxui::Dimension::Full())) {}

void TuiStreamWriter::writeError(const std::string& errorText) {
    std::cerr << errorText << std::endl;
}

void TuiStreamWriter::writeStatusItems(const std::vector<StatusItem>& statusItems) {
    ftxui::Elements statusElements;
    for (const StatusItem& statusItem : statusItems) {
        ftxui::Element nameElement = ftxui::text(statusItem.getName());
        ftxui::Element separatorElement = ftxui::separator();
        ftxui::Element textElement = ftxui::text(statusItem.getText());

        const std::optional<ftxui::Color> fgColor = statusItem.getForegroundColor()
                                                        .transform([](const StatusItem::Color&& color) {
                                                            return ftxui::Color(color.red, color.green, color.blue);
                                                        });
        if (fgColor) {
            nameElement |= ftxui::color(fgColor.value());
            textElement |= ftxui::color(fgColor.value());
        }

        const std::optional<ftxui::Color> borderColor = statusItem.getBorderColor()
                                                            .transform([](const StatusItem::Color&& color) {
                                                                return ftxui::Color(color.red, color.green, color.blue);
                                                            });
        if (borderColor) {
            separatorElement |= ftxui::color(borderColor.value());
        }

        statusElements.push_back(ftxui::hbox({nameElement, separatorElement, textElement}) |
                                 (borderColor ? ftxui::borderStyled(borderColor.value()) : ftxui::border));
    }
    mScreen.Clear();
    ftxui::Render(mScreen, ftxui::vbox(statusElements));
    std::cout << mScreen.ResetPosition() << mScreen.ToString() << std::flush;
}
