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

#include <Krum/misc/StringUtils.hpp>

namespace Krum::misc
{
	std::vector<std::string> StringUtils::split(const std::string &input, char delimiter)
	{
		std::vector<std::string> result;
		std::stringstream ss(input);
		std::string token;

		while (std::getline(ss, token, delimiter))
		{
			result.push_back(token);
		}

		return result;
	}

	std::string_view StringUtils::trim(std::string_view input)
	{
		while (!input.empty() && std::isspace(input.front()))
		{
			input.remove_prefix(1);
		}

		while (!input.empty() && std::isspace(input.back()))
		{
			input.remove_suffix(1);
		}

		return input;
	}

	bool StringUtils::contains(std::string base, std::string extra)
	{
		return base.find(extra.c_str()) != std::string::npos;
	}
}
