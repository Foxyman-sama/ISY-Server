#include "network/acceptor.hpp"

void Acceptor::handler(const boost::system::error_code &_error) noexcept { 
    if (!_error) {
        std::string ip { mp_socket->remote_endpoint().address().to_string() };
        OUTPUT("Connected: " << ip, FOREGROUND_GREEN)
        Handler::processSocket(mp_socket);
    }
    else {
        delete mp_socket;
    }

    start();
}

void Acceptor::start() noexcept { 
    mp_socket = new tcp::socket { m_io };
    m_acceptor.async_accept(
        *mp_socket, 
         boost::bind(
             &Acceptor::handler,
              this,
              boost::asio::placeholders::error
         )
    );
}
