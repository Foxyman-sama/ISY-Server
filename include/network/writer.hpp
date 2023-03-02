#ifndef NETWORK_WRITER_HPP
#define NETWORK_WRITER_HPP

#include "libs.hpp"

class Writer {
public:
    static boost::asio::awaitable<void> send(tcp::socket                        *_p_socket,
                                             std::vector<std::shared_ptr<Data>>  _vector) noexcept;
    static boost::asio::awaitable<void> waitStatus(tcp::socket *_p_socket) noexcept;
};

#endif
