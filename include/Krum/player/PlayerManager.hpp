// Krum - Krum mcpe 0.14-1.1 server software.
//
// Copyright (C) 2024  Krum-SSFM.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include "Player.hpp"
#include <map>
#include <string>
#include <Krum/misc/StringUtils.hpp>

namespace Krum::player
{
    class PlayerManager
    {
    private:
        std::map<std::string, Player *, misc::StringComparator> list;

    public:
        bool has(std::string real_name);

        Player *get(std::string real_name);

        bool add(Player *player);

        bool remove(std::string real_name);
    };
}