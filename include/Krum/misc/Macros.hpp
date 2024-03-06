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

#include <random>

#ifndef INVOKE_CALLBACK_IF_VALID
#define INVOKE_CALLBACK_IF_VALID(callback, ...) \
	if (callback)                               \
	{                                           \
		callback(__VA_ARGS__);                  \
	}
#endif

#ifndef INVOKE_CALLBACK_IF_VALID_NOT_VOID
#define INVOKE_CALLBACK_IF_VALID_NOT_VOID(callback, result, ...) \
	if (callback)                                                \
	{                                                            \
		result = callback(__VA_ARGS__);                          \
	}
#endif

#ifndef GENERATE_RANDOM_UINT64
#define GENERATE_RANDOM_UINT64(var)                              \
	static std::random_device rd;                                \
	static std::mt19937_64 generator(rd());                      \
	static std::uniform_int_distribution<uint64_t> distribution; \
	var = distribution(generator);
#endif
