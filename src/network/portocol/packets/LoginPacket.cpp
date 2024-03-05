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

#include <Krum/network/protocol/packets/LoginPacket.hpp>

namespace Krum::network::protocol::packets
{
	LoginPacket::LoginPacket(Binary::Buffer *buffer, std::size_t position)
		: BasePacket(buffer, position)
	{
	}

	packet_identifier_t LoginPacket::getId() const
	{
		return PacketIdentifiers::LOGIN;
	}

	void LoginPacket::deserializeBody()
	{
		this->real_name = this->readString<std::uint16_t>();
		this->ignoreBytes(sizeof(std::uint32_t)); // used to check if is network order, by reading a uint32 from stream then checking if it's equals to 0x2d, but it's useless for me
		this->protocol_version = this->read<std::uint32_t>();

		if (this->protocol_version == 0x2d)
		{
			this->skin_id = this->read<std::uint64_t>();
			this->skin_uuid = this->readUUID();
			this->server_address = this->readString<std::uint16_t>();
			this->field_7 = this->readString<std::uint16_t>();
			this->skin_name = this->readString<std::uint16_t>();
			this->field_9 = this->readString<std::uint16_t>();
		}
	}

	void LoginPacket::serializeBody()
	{
		this->writeString<std::uint16_t>(this->real_name);

		this->write<std::uint32_t>(0x2d);
		this->write<std::uint32_t>(this->protocol_version);

		if (this->protocol_version == 0x2d)
		{
			this->write<std::uint64_t>(this->skin_id);
			this->writeUUID(this->skin_uuid);
			this->writeString<std::uint16_t>(this->server_address);
			this->writeString<std::uint16_t>(this->field_7);
			this->writeString<std::uint16_t>(this->skin_name);
			this->writeString<std::uint16_t>(this->field_9);
		}
	}
}
