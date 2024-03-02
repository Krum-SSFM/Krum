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
    BasePacket::BasePacket(Binary::Buffer *buffer, size_t position)
        : BinaryStream::BinaryStream(buffer, position)
    {
    }

    BasePacket::~BasePacket()
    {
        BinaryStream::~BinaryStream();
    }

    void BasePacket::deserializie()
    {
        if (this->getPosition() != 0)
        {
            this->rewind();
        }
        this->deserializieHeader();
        this->deserializieBody();
    }

    void BasePacket::deserializieHeader()
    {
        if (this->read<std::uint8_t>() != this->getId())
        {
            std::cout << "Invalid packet id" << std::endl;
            // exit(0);
        }
    }

    void BasePacket::serializie()
    {
        if (this->getBuffer()->getPosition() != 0)
        {
            this->reset(true);
        }
        this->serializieHeader();
        this->serializieBody();
    }

    void BasePacket::serializieHeader()
    {
        this->write<std::uint8_t>(this->getId());
    }
}
