#ifndef NETWORK_ACCEPTOR_HPP
#define NETWORK_ACCEPTOR_HPP

#include <iostream>
#include "system/handler.hpp"

class Acceptor {
private:
    boost::asio::io_context &m_io;
    tcp::acceptor            m_acceptor;
    tcp::socket             *mp_socket;

private:
    void handler(const boost::system::error_code &_error) noexcept;

public:
    explicit Acceptor(boost::asio::io_context &_io) noexcept 
        : m_io { _io }
        , m_acceptor { _io, tcp::endpoint { tcp::v4(), 9090 } }
        , mp_socket { } { }

    void start() noexcept;
};

#endif
