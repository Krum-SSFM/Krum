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

#include <RakNet/RakNetTypes.h>
#include <string>
#include <cstdint>

namespace Krum::player
{
	class Player
	{
	private:
		std::string real_name;
		RakNet::SystemAddress address;
		std::uint32_t protocol_version;

	public:
		Player(std::string real_name, RakNet::SystemAddress address);
		// ~Player();

		decltype(real_name) getRealName() const { return this->real_name; };
		void setRealName(decltype(real_name) value) { this->real_name = value; };
		decltype(protocol_version) getProtocolVersion() const { return this->protocol_version; };
		void setProtocolVersion(decltype(protocol_version) value) { this->protocol_version = value; };

		decltype(address) getAddress() const { return this->address; };
	};
}
