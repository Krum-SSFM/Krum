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

#include <string>
#include <cstdint>
#include <Krum/misc/Macros.hpp>
#include <vector>

namespace Krum::commands
{
    class Command
    {
    private:
        std::string name;
        std::string description;
        std::uint8_t permissionLevel;

    public:
        Command(const std::string &name, const std::string &description, std::uint8_t permissionLevel);

        virtual ADD_GETTER(Name, name);
        virtual ADD_GETTER(Description, description);
        virtual ADD_GETTER(PermissionLevel, permissionLevel);

        virtual void handleExecution(const std::string &commandName, void *source, std::vector<std::string> arguments) = 0;
    };
}
