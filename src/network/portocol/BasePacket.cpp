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

#include <Krum/network/protocol/BasePacket.hpp>
#include <iostream> // temp

namespace Krum::network::protocol
{
    BasePacket::BasePacket(Binary::Buffer *buffer, std::size_t position)
        : misc::MinecraftBinaryStream(buffer, position)
    {
    }

    void BasePacket::deserialize()
    {
        this->deserializeHeader();
        this->deserializeBody();
    }

    void BasePacket::deserializeHeader() // todo do an arg to add if header byte required
    {
        if (static_cast<packet_identifier_t>(this->read<std::uint8_t>() - protocol::OLDV_PACKET_HEADER_BYTE) != this->getId())
        {
            std::cout << "Invalid packet id" << std::endl;
            // exit(0);
        }
    }

    void BasePacket::serialize()
    {
        this->serializeHeader();
        this->serializeBody();
    }

    void BasePacket::serializeHeader() // todo do an arg to add if header byte required
    {
        this->write<std::uint8_t>(static_cast<std::uint8_t>(this->getId()) +  protocol::OLDV_PACKET_HEADER_BYTE);
    }
}
