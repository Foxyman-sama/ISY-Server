#ifndef SYSTEM_HANDLER_HPP
#define SYSTEM_HANDLER_HPP

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include "network/reader.hpp"

#define OUTPUT(text, color)                \
    SetConsoleTextAttribute(g_cmd, color); \
    std::cout << text << '\n';             \
    SetConsoleTextAttribute(g_cmd, 7);

using tcp = boost::asio::ip::tcp;

inline static HANDLE g_cmd { GetStdHandle(STD_OUTPUT_HANDLE) };

class Handler {
private:
    inline static std::shared_ptr<Data> mp_data { std::make_shared<Data>() };
    inline static std::vector<char>     m_buf { };

private:
    static void handler(tcp::socket                     *_p_socket,
                        const boost::system::error_code &_error, 
                        size_t                           _bytes_t) noexcept;
    static void prepareDataBuffer() noexcept;

public:
    static void processSocket(tcp::socket *_p_socket) noexcept;
};

#endif
