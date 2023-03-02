#ifndef LIBS_HPP
#define LIBS_HPP

#include <iostream>
#include <fstream>
#include <random>
#include <filesystem>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include "network/data.hpp"

#define OUTPUT(text, color)                \
    SetConsoleTextAttribute(g_cmd, color); \
    std::cout << text << '\n';             \
    SetConsoleTextAttribute(g_cmd, 7);

using tcp     = boost::asio::ip::tcp;
using DataPtr = std::shared_ptr<Data>;

inline static HANDLE g_cmd { GetStdHandle(STD_OUTPUT_HANDLE) };

#endif
