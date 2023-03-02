#ifndef SYSTEM_HANDLER_HPP
#define SYSTEM_HANDLER_HPP

#include "libs.hpp"
#include "network/reader.hpp"
#include "network/writer.hpp"
#include "system/system.hpp"

class Handler {
private:
    inline static std::shared_ptr<Data> mp_data { std::make_shared<Data>() };
    inline static std::vector<char>     m_command { };

private:    
    static boost::asio::awaitable<void> read(tcp::socket *_p_socket) noexcept {
        prepare();
        co_await boost::asio::async_read(
            *_p_socket,
             boost::asio::buffer(m_command),
             boost::asio::transfer_at_least(1),
             boost::asio::use_awaitable
        );    
        co_await Reader::sendStatus(_p_socket);
    }
    static void                         prepare() noexcept;

public:
    static boost::asio::awaitable<void> processSocket(tcp::socket *_p_socket) noexcept;
};

#endif
