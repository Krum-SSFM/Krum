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

#include <Krum/player/PlayerManager.hpp>

namespace Krum::player
{
    bool PlayerManager::has(std::string real_name)
    {
        return this->list.find(real_name) != this->list.end();
    }

    Player *PlayerManager::get(std::string real_name)
    {
        if (!this->has(real_name))
        {
            return nullptr;
        }

        return this->list.at(real_name);
    }

    bool PlayerManager::add(Player *player)
    {
        auto real_name = std::string(player->getRealName());

        if (this->has(real_name))
        {
            return false;
        }

        this->list.insert({real_name, player});
        return true;
    }

    bool PlayerManager::remove(std::string real_name)
    {
        if (!this->has(real_name))
        {
            return false;
        }

        this->list.erase(real_name);
        return true;
    }
}
