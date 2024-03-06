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
		spdlog::info("constructor called with ip and port {}:{}", ip, port);

		this->peer->SetMaximumIncomingConnections(max_players);

		Binary::BinaryStream temp_stream(Binary::Buffer::allocateZero(), 0);
		temp_stream.writeString<std::uint16_t>("MCPE;Krum Server;45;0.14;0;10;13253860892328930865;World;Survival");

		this->peer->SetOfflinePingResponse(reinterpret_cast<char *>(temp_stream.getBuffer()->getBinary()), temp_stream.getBuffer()->getPosition());

		this->packet_manager = new network::protocol::PacketManager();
		this->command_manager = new commands::CommandManager();
		this->session_manager = new network::SessionManager();
		this->player_manager = new player::PlayerManager();
	}

	Server::~Server()
	{
		this->shutdown();
		spdlog::info("Destructor Called");
	}

	void Server::shutdown()
	{
		this->peer->Shutdown(1000, 0);
		delete this->packet_manager;
		delete this->command_manager;
		delete this->session_manager;
		delete this->player_manager;
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

		spdlog::info("Server running");

		RakNet::StartupResult r = this->peer->Startup(this->max_players, &RakNet::SocketDescriptor(this->port, this->ip.c_str() == "0.0.0.0" ? 0 : this->ip.c_str()), 1);
		if (r != RakNet::RAKNET_STARTED)
		{
			spdlog::info("Unable to startup raknet. Error code: {}", r);
			return;
		}

		while (true)
		{
			for (RakNet::Packet *packet = this->peer->Receive(); packet; this->peer->DeallocatePacket(packet), packet = this->peer->Receive())
			{
				std::uint8_t id = packet->data[0];
				auto address = packet->systemAddress.ToString(true);

				if (id == ID_NEW_INCOMING_CONNECTION)
				{
					if (!this->session_manager->add(packet->systemAddress))
						continue;

					spdlog::info("New incoming connection: {}", address);
				}
				else if (id == ID_DISCONNECTION_NOTIFICATION)
				{
					if (!this->session_manager->remove(address))
						continue;

					spdlog::info("Disconnection: {}", address);
				}
				else if (id > ID_USER_PACKET_ENUM)
				{
					if (!this->session_manager->has(address))
						continue;

					if (id == network::protocol::OLDV_PACKET_HEADER_BYTE)
					{
						auto stream = new Binary::BinaryStream(new Binary::Buffer(packet->data, packet->length), 1);

						auto game_packet_id = static_cast<network::protocol::packet_identifier_t>(stream->read<std::uint8_t>() - network::protocol::OLDV_PACKET_HEADER_BYTE);
						if (!this->packet_manager->has(game_packet_id))
						{
							spdlog::info("PacketId not registered in manager");
							continue;
						}

						auto game_packet = this->packet_manager->get(game_packet_id);
						game_packet->setBuffer(stream->getBuffer());
						game_packet->setPosition(1);
						game_packet->deserialize();

						if (game_packet->getId() == network::protocol::PacketIdentifiers::LOGIN)
						{
							auto login = static_cast<network::protocol::packets::LoginPacket *>(game_packet);

							spdlog::info("Login packet fields: ");
							spdlog::info(login->getRealName());
							spdlog::info(login->getProtocolVersion());
							spdlog::info(login->getSkinId());
							spdlog::info(uuids::to_string(login->getSkinUUID()));
							spdlog::info(login->getServerAddress());
							spdlog::info(login->getField7());
							spdlog::info(login->getSkinName());
							spdlog::info(login->getField9());

							// this->player_manager->add(new player::Player(login->getRealName(), packet->systemAddress, this->peer));
						}
					}
				}
			}
		}
	}
}
