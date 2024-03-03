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
#include <Krum/misc/Macros.hpp>
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

        ADD_GETTER_AND_SETTER(RealName, real_name);
        ADD_GETTER_AND_SETTER(ProtocolVersion, protocol_version);
        ADD_GETTER_AND_SETTER(SkinId, skin_id);
        ADD_GETTER_AND_SETTER(SkinUUID, skin_uuid);
        ADD_GETTER_AND_SETTER(ServerAddress, server_address);
        ADD_GETTER_AND_SETTER(Field7, field_7);
        ADD_GETTER_AND_SETTER(SkinName, skin_name);
        ADD_GETTER_AND_SETTER(Field9, field_9);

        void deserializeBody() override;

        void serializeBody() override;
    };
}
