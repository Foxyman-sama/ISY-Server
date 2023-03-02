#ifndef NETWORK_READER_HPP
#define NETWORK_READER_HPP

#include "libs.hpp"

class Reader {
public:
    static boost::asio::awaitable<void> receive(tcp::socket           *_p_socket,
                                             std::shared_ptr<Data>  _p_data) noexcept;
    static boost::asio::awaitable<void> sendStatus(tcp::socket *_p_socket) noexcept;
};

#endif
