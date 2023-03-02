#ifndef NETWORK_ACCEPTOR_HPP
#define NETWORK_ACCEPTOR_HPP

#include <iostream>
#include "system/handler.hpp"

class Acceptor {
private:
    boost::asio::io_context &m_io;

public:
    explicit Acceptor(boost::asio::io_context &_io) noexcept 
        : m_io { _io } { }

    boost::asio::awaitable<void> start() noexcept;
};

#endif
