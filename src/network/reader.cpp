#include "network/reader.hpp"

boost::asio::awaitable<void> Reader::receive(tcp::socket           *_p_socket,
                                             std::shared_ptr<Data>  _p_data) noexcept { 
    try {
        co_await boost::asio::async_read(
            *_p_socket,
             boost::asio::buffer(&_p_data->m_size, sizeof(uint64_t)),
             boost::asio::use_awaitable
        );  
        co_await sendStatus(_p_socket);
        co_await boost::asio::async_read(
            *_p_socket,
             boost::asio::buffer(_p_data->m_type),
             boost::asio::transfer_at_least(4),
             boost::asio::use_awaitable
        );          
        co_await sendStatus(_p_socket);

        auto   *p_vec { &_p_data->m_data };
        size_t  size { };
        auto    start { std::chrono::steady_clock::now() };
        p_vec->resize(_p_data->m_size);
        for (size_t i { }; i < _p_data->m_size; i += size) {
            size = co_await boost::asio::async_read(
                *_p_socket,
                 boost::asio::buffer(p_vec->data() + i, _p_data->m_size - i > g_PACKET_SIZE 
                                                        ? g_PACKET_SIZE 
                                                        : _p_data->m_size - i),
                 boost::asio::transfer_at_least(1),
                 boost::asio::use_awaitable
            );

            co_await sendStatus(_p_socket);
        }

        auto   end { std::chrono::steady_clock::now() };
        bool   is_all { _p_data->m_data.size() == _p_data->m_size };
        size_t delta {
            static_cast<size_t>(std::chrono::duration<double, std::milli>(end - start).count())
        };
        OUTPUT("\nsize expected:     " << _p_data->m_size, 3);
        OUTPUT("size transfered:   " << _p_data->m_data.size(), 3);
        OUTPUT("is all transfered: " << std::boolalpha << is_all, 3);
        OUTPUT("type:              " << _p_data->m_type.data(), 3);
        OUTPUT("time:              " << delta << "ms", 3);
    }
    catch (const std::exception &e) {
        std::cerr << '\n' << e.what() << "\n\n";
    }
}
boost::asio::awaitable<void> Reader::sendStatus(tcp::socket *_p_socket) noexcept {
    try {
        co_await boost::asio::async_write(
            *_p_socket,
             boost::asio::buffer("r"),
             boost::asio::use_awaitable
        );
    }
    catch (const std::exception &e) {
        std::cerr << '\n' << e.what() << "\n\n";
    }

    co_return;
}