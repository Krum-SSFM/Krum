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

#include <Krum/misc/MinecraftBinaryStream.hpp>
#include "PacketIdentifiers.hpp"

namespace Krum::network::protocol
{
	class BasePacket : public misc::MinecraftBinaryStream
	{
	public:
		BasePacket(Binary::Buffer *buffer, std::size_t position);

		virtual packet_identifier_t getId() const = 0;

		virtual void deserialize();
		virtual void deserializeHeader();
		virtual void deserializeBody() = 0;

		virtual void serialize();
		virtual void serializeHeader();
		virtual void serializeBody() = 0;
	};
}
