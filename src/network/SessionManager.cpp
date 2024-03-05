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

#include <Krum/network/SessionManager.hpp>

namespace Krum::network
{
	bool SessionManager::has(std::string address)
	{
		return this->list.find(address) != this->list.end();
	}

	RakNet::SystemAddress SessionManager::get(std::string address)
	{
		if (!this->has(address))
		{
			return nullptr;
		}

		return this->list.at(address);
	}

	bool SessionManager::add(RakNet::SystemAddress address)
	{
		auto str_address = std::string(address.ToString(true));

		if (this->has(str_address))
		{
			return false;
		}

		this->list.insert({str_address, address});
		return true;
	}

	bool SessionManager::remove(std::string address)
	{
		if (!this->has(address))
		{
			return false;
		}

		this->list.erase(address);
		return true;
	}
}
