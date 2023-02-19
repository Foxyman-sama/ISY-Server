#include "network/reader.hpp"

void Reader::handlerForSize(tcp::socket                     *_p_socket,
                            std::shared_ptr<Data>            _p_data,
                            const boost::system::error_code &_error,
                            size_t                           _bytes_t) noexcept { 
    m_expected = _p_data->m_size;
    boost::asio::async_read(
        *_p_socket,
         boost::asio::buffer(_p_data->m_type, 4),
         boost::asio::transfer_at_least(1),
         boost::bind(
             &Reader::handlerForType,
              _p_socket,
              _p_data,
              boost::asio::placeholders::error,
              boost::asio::placeholders::bytes_transferred
         )
    );
}
void Reader::handlerForType(tcp::socket                     *_p_socket,
                            std::shared_ptr<Data>            _p_data,
                            const boost::system::error_code &_error,
                            size_t                           _bytes_t) noexcept { 
    m_temp.clear();
    m_temp.resize(g_PACKET_SIZE);
    boost::asio::async_read(
        *_p_socket,
         boost::asio::buffer(m_temp),
         boost::asio::transfer_at_least(1),
         boost::bind(
             &Reader::handlerForData,
              _p_socket,
              _p_data,
              boost::asio::placeholders::error,
              boost::asio::placeholders::bytes_transferred
         )
    );
}
void Reader::handlerForData(tcp::socket                     *_p_socket,
                            std::shared_ptr<Data>            _p_data,
                            const boost::system::error_code &_error,
                            size_t                           _bytes_t) noexcept {
    if (!_error) {
        m_expected -= _bytes_t;
        for (size_t i { }; i < _bytes_t; ++i) {
            _p_data->m_data.emplace_back(m_temp[i]);
        }

        if (m_expected > 0) {
            m_temp.clear();
            m_temp.resize(g_PACKET_SIZE);
            boost::asio::async_read(
                *_p_socket,
                 boost::asio::buffer(m_temp),
                 boost::asio::transfer_at_least(1),
                 boost::bind(
                     &Reader::handlerForData,
                      _p_socket,
                      _p_data,
                      boost::asio::placeholders::error,
                      boost::asio::placeholders::bytes_transferred
                 )
            );
        }
    }
    else {
        delete _p_socket;
    }
}

void Reader::read(tcp::socket           *_p_socket,
                  std::shared_ptr<Data>  _p_data) noexcept {              
    co_await boost::asio::async_read(
        *_p_socket,
        boost::asio::buffer(&_p_data->m_size, sizeof(uint64_t)),
        boost::asio::transfer_at_least(1),
        boost::asio::use_awaitable
    ); 

}
