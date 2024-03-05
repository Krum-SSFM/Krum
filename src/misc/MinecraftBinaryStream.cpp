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

#include <Krum/misc/MinecraftBinaryStream.hpp>
#include <iostream>

namespace Krum::misc
{
	MinecraftBinaryStream::MinecraftBinaryStream(Binary::Buffer *buffer, std::size_t position)
		: BinaryStreamMod(buffer, position)
	{
	}

	void MinecraftBinaryStream::writeUUID(const uuids::uuid &value)
	{
		this->getBuffer()->writeAligned(const_cast<std::uint8_t *>(reinterpret_cast<const std::uint8_t *>(value.as_bytes().data())), value.as_bytes().size());
	}

	uuids::uuid MinecraftBinaryStream::readUUID()
	{
		uuids::uuid::value_type bytes[16] = {};

		std::memcpy(bytes, this->readAligned(16)->getBinary(), 16);

		return uuids::uuid(std::begin(bytes), std::end(bytes));
	}
}
