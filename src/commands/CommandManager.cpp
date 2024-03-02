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

#include <Krum/commands/CommandManager.hpp>
#include <iostream>

namespace Krum::commands
{
    CommandManager::CommandManager()
    {
        this->add(new list::Help());
        this->add(new list::Exit());
    }

    bool CommandManager::has(std::string name)
    {
        return this->list.find(name) != this->list.end();
    }

    Command *CommandManager::get(std::string name)
    {
        if (!this->has(name))
        {
            return nullptr;
        }

        return this->list.at(name);
    }

    bool CommandManager::add(Command *command)
    {
        if (this->has(command->getName()))
        {
            return false;
        }

        this->list.insert({command->getName(), command});
        return true;
    }

    bool CommandManager::remove(std::string name)
    {
        if (!this->has(name))
        {
            return false;
        }

        this->list.erase(name);
        return true;
    }

    bool CommandManager::executeCommand(const std::string &command)
    {
        if (misc::StringUtils::trim(command) == "")
        {
            return true;
        }

        auto temp_cmd = std::string(command);
        std::vector<std::string> arguments;

        if (misc::StringUtils::contains(temp_cmd, " "))
        {
            auto command_parts = misc::StringUtils::split(command, ' ');
            temp_cmd = command_parts.at(0);
            command_parts.erase(command_parts.begin());
            arguments = command_parts;
        }

        if (!this->has(temp_cmd))
        {
            return false;
        }

        auto actual_command = this->get(temp_cmd);

        if (actual_command == nullptr)
        {
            return false;
        }

        actual_command->handleExecution(temp_cmd, nullptr, arguments);
        return true;
    }
}
