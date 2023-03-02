#include "network/writer.hpp"

boost::asio::awaitable<void> Writer::send(tcp::socket                        *_p_socket,
                                          std::vector<std::shared_ptr<Data>>  _vector) noexcept {
    try {
        uint64_t size_v { _vector.size() };
        co_await boost::asio::async_write(
            *_p_socket,
             boost::asio::buffer(&size_v, sizeof(uint64_t)),
             boost::asio::use_awaitable
        );
        co_await waitStatus(_p_socket);

        for (size_t i { }; i < size_v; ++i) {
            uint64_t size { _vector[i]->m_data.size() };
            co_await boost::asio::async_write(
                *_p_socket,
                 boost::asio::buffer(&size, sizeof(uint64_t)),
                 boost::asio::use_awaitable
            );
            co_await waitStatus(_p_socket);
            co_await boost::asio::async_write(
                *_p_socket,
                 boost::asio::buffer((_vector[i])->m_data),
                 boost::asio::use_awaitable
            );
            co_await waitStatus(_p_socket);
        }
    }
    catch (const std::exception &e) {
        std::cerr << '\n' << e.what() << "\n\n";
    }
}
boost::asio::awaitable<void> Writer::waitStatus(tcp::socket *_p_socket) noexcept { 
    try {
        char readed[2] { };
        while (strcmp(readed, "r")) {
            co_await boost::asio::async_read(
                *_p_socket,
                 boost::asio::buffer(readed),
                 boost::asio::use_awaitable
            );
        }
    }
    catch (const std::exception &e) {
        std::cerr << '\n' << e.what() << "\n\n";
    }

    co_return;
}

