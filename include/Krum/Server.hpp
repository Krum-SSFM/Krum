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

#include <iostream>
#include <RakNet/RakPeerInterface.h>
#include <RakNet/MessageIdentifiers.h>
#include <Krum/commands/CommandManager.hpp>
#include <thread>
#include <cstdint>
#include <BinaryStream/BinaryStream.hpp>
#include <Krum/network/protocol/PacketManager.hpp>

namespace Krum
{
    class Server
    {
    private:
        std::string ip;
        std::uint16_t port;
        std::uint16_t max_players;
        RakNet::RakPeerInterface *peer;
        network::protocol::PacketManager *packet_manager;
        commands::CommandManager *command_manager;

    public:

        Server(const std::string &ip, std::uint16_t port, std::uint16_t max_players);

        ~Server();

        void shutdown();

        void start();
    };
}
