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

#include "BinaryStreamMod.hpp"
#include <string>
#include <cstdint>
#include "StringUtils.hpp"
#include <uuid.h>

namespace Krum::misc
{
	class MinecraftBinaryStream : public BinaryStreamMod
	{
	public:
		MinecraftBinaryStream(Binary::Buffer *buffer, std::size_t position);

		void writeUUID(const uuids::uuid &value);

		uuids::uuid readUUID();
	};
}
