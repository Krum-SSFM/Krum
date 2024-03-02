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

#include <Krum/Server.hpp>

namespace Krum
{
    Server::Server(const std::string &ip, std::uint16_t port, std::uint16_t max_players)
        : ip(ip), port(port), peer(RakNet::RakPeerInterface::GetInstance())
    {
        std::cout << "constructor called with ip and port " << ip << ":" << port << std::endl;

        this->peer->SetMaximumIncomingConnections(max_players);

        Binary::BinaryStream temp_stream(Binary::Buffer::allocateZero(), 0);
        temp_stream.writeString<std::uint16_t>("MCPE;Krum Server;45;0.14;0;10;13253860892328930865;World;Survival");

        this->peer->SetOfflinePingResponse(reinterpret_cast<char *>(temp_stream.getBuffer()->getBinary()), temp_stream.getBuffer()->getPosition());

        this->packet_manager = new network::protocol::PacketManager();
        this->command_manager = new commands::CommandManager();
    }

    Server::~Server()
    {
        this->shutdown();
        std::cout << "Destructor Called" << std::endl;
    }

    void Server::shutdown()
    {
        this->peer->Shutdown(0, 0);
        delete this->packet_manager;
        delete this->command_manager;
        // todo delete this->thread_manager;
    }

    void Server::start()
    {
        auto command_manager_ts = this->command_manager;
        std::thread command_thread([&command_manager_ts]()
                                   {
                while (true)
                {
                    std::string user_input;
                    std::getline(std::cin, user_input);

                    if (user_input.length() > 0)
                    {
                        if (!command_manager_ts->executeCommand(user_input))
                        {
                            // todo do senders
                        }
                    }
            } });

        command_thread.detach();

        std::cout << "Server running" << std::endl;

        if (this->peer->Startup(this->max_players, &RakNet::SocketDescriptor(this->port, this->ip.c_str()), 1) != RakNet::RAKNET_STARTED)
        {
            std::cout << "Unable to startup raknet." << std::endl;
            return;
        }

        while (true)
        {
            for (RakNet::Packet *packet = this->peer->Receive(); packet; this->peer->DeallocatePacket(packet), packet = this->peer->Receive())
            {
                std::uint8_t id = packet->data[0];

                if (id == ID_NEW_INCOMING_CONNECTION)
                {
                    std::cout << "New incoming connection: " << packet->systemAddress.ToString(true) << std::endl;
                }
                else if (id == ID_DISCONNECTION_NOTIFICATION)
                {
                    std::cout << "Disconnection: " << packet->systemAddress.ToString(true) << std::endl;
                }
                else if (id >= ID_USER_PACKET_ENUM)
                {
                    std::cout << "Game packet id: " << std::to_string(id) << std::endl;
                }
            }
        }
    }
}
