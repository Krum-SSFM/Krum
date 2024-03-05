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

#include <BinaryStream/BinaryStream.hpp>
#include <iostream>
#include <fstream>
#include <Krum/Server.hpp>
#include <map>
#include <Krum/commands/CommandManager.hpp>
#include <csignal>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/async.h>
#include <pugixml.hpp>

namespace
{
	volatile std::sig_atomic_t g_signal_status;
}

int main()
{
	pugi::xml_document properties;

	pugi::xml_parse_result result = properties.load_file("properties.xml");
	if (!result)
	{
		std::cerr << "Unable to load properties.xml file" << std::endl;
		return 1;
	}

	auto krum_element = properties.child("Krum");

	auto address_child = krum_element.child("Address");
	auto motd_child = krum_element.child("Motd");

	spdlog::init_thread_pool(8192, 1);

	auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("server.log", 1048576, 3);
    auto async_logger = std::make_shared<spdlog::async_logger>("Server", spdlog::sinks_init_list({console_sink, file_sink}), spdlog::thread_pool(), spdlog::async_overflow_policy::block);

    spdlog::set_default_logger(async_logger);

    async_logger->flush_on(spdlog::level::info);

	Krum::Server server(address_child.child("Interface").text().as_string(), address_child.child("Port").text().as_uint(), motd_child.child("MaxPlayers").text().as_uint());

	std::signal(SIGINT, [](int signum)
				{ g_signal_status = signum; });

	std::thread signal_thread([&server]()
							  {
        while (true)
        {
            if (g_signal_status != NULL)
            {
                break;
            }
        }

        spdlog::info("Server killed!");
        server.shutdown();
        exit(g_signal_status); });

	signal_thread.detach();
	server.start();

	return 0;
}
