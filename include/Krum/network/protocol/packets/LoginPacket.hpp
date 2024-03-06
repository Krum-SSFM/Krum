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

#include <Krum/network/protocol/BasePacket.hpp>
#include <string>
#include <cstdint>
#include <BinaryStream/BinaryStream.hpp>
#include <uuid.h>

namespace Krum::network::protocol::packets
{
	class LoginPacket : public BasePacket
	{
	private:
		std::string real_name;
		std::uint32_t protocol_version;
		std::uint64_t skin_id;
		uuids::uuid skin_uuid;
		std::string server_address;
		std::string field_7;
		std::string skin_name;
		std::string field_9;

	public:
		LoginPacket(Binary::Buffer *buffer, std::size_t position);

		packet_identifier_t getId() const override;

		decltype(real_name) getRealName() { return this->real_name; };
		void setRealName(decltype(real_name) value) { this->real_name = value; };
		decltype(protocol_version) getProtocolVersion() { return this->protocol_version; };
		void setProtocolVersion(decltype(protocol_version) value) { this->protocol_version = value; };
		decltype(skin_id) getSkinId() { return this->skin_id; };
		void setSkinId(decltype(skin_id) value) { this->skin_id = value; };
		decltype(skin_uuid) getSkinUUID() { return this->skin_uuid; };
		void setSkinUUID(decltype(skin_uuid) value) { this->skin_uuid = value; };
		decltype(server_address) getServerAddress() { return this->server_address; };
		void setServerAddress(decltype(server_address) value) { this->server_address = value; };
		decltype(field_7) getField7() { return this->field_7; };
		void setField7(decltype(field_7) value) { this->field_7 = value; };
		decltype(skin_name) getSkinName() { return this->skin_name; };
		void setSkinName(decltype(skin_name) value) { this->skin_name = value; };
		decltype(field_9) getField9() { return this->field_9; };
		void setField9(decltype(field_9) value) { this->field_9 = value; };

		void deserializeBody() override;

		void serializeBody() override;
	};
}
