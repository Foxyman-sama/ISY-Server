#include "network/acceptor.hpp"

boost::asio::awaitable<void> Acceptor::start() noexcept {
    try {
        tcp::acceptor acceptor { m_io, { tcp::v4(), 9090 } };
        while (true) {
            tcp::socket *result { new tcp::socket {
                co_await acceptor.async_accept(boost::asio::use_awaitable)
            } };
            boost::asio::co_spawn(
                m_io,
                Handler::processSocket(result),
                boost::asio::detached
            );
        }
    }
    catch (const std::exception &e) {
        std::cerr << "Acceptor::start()\n" << e.what() << '\n';
    }
}
