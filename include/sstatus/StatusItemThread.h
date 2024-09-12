/*
 * StatusItemThread.h - Status item specific thread header
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

#ifndef STATUSITEMTHREAD_H
#define STATUSITEMTHREAD_H

#include <atomic>
#include <thread>

#include "sstatus/StatusItem.h"

class StatusItemThread : public std::thread {
  public:
    explicit StatusItemThread(int id, StatusItem& statusItem, std::atomic_flag& notifyFlag);

  private:
    static void run(int id, StatusItem& statusItem, std::atomic_flag& notifyFlag);

    static constexpr std::string loadingText = "Loading...";
};

#endif
