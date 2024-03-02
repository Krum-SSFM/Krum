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

namespace
{
    volatile std::sig_atomic_t g_signal_status;
}

int main(int argc, char **argv)
{
    std::string ip = argv[1];
    auto port = static_cast<std::uint16_t>(std::stoi(argv[2]));

    Krum::Server server(ip, port, 10);

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

        std::cout << "Server killed!" << std::endl;
        server.shutdown();
        exit(g_signal_status); });

    signal_thread.detach();
    server.start();

    return 0;
}
