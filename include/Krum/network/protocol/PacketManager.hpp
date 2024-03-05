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

#include <map>
#include "BasePacket.hpp"
#include <Krum/network/protocol/packets/LoginPacket.hpp>

namespace Krum::network::protocol
{
	class PacketManager
	{
	private:
		std::map<protocol::packet_identifier_t, BasePacket *> list;

	public:
		PacketManager();

		bool has(protocol::packet_identifier_t id);

		BasePacket *get(protocol::packet_identifier_t id);

		bool add(BasePacket *packet);

		bool remove(protocol::packet_identifier_t id);
	};
}
