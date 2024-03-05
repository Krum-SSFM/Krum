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

#include <Krum/network/protocol/PacketManager.hpp>

namespace Krum::network::protocol
{
	PacketManager::PacketManager()
	{
		this->add(new packets::LoginPacket(Binary::Buffer::allocateZero(), 0));
	}

	bool PacketManager::has(protocol::packet_identifier_t id)
	{
		return this->list.find(id) != this->list.end();
	}

	BasePacket *PacketManager::get(protocol::packet_identifier_t id)
	{
		if (!this->has(id))
		{
			return nullptr;
		}

		return this->list.at(id);
	}

	bool PacketManager::add(BasePacket *packet)
	{
		if (this->has(packet->getId()))
		{
			return false;
		}

		this->list.insert({packet->getId(), packet});
		return true;
	}

	bool PacketManager::remove(protocol::packet_identifier_t id)
	{
		if (!this->has(id))
		{
			return false;
		}

		this->list.erase(id);
		return true;
	}
}
