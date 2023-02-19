#ifndef NETWORK_READER_HPP
#define NETWORK_READER_HPP

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/asio/use_future.hpp>
#include "data.hpp"

using tcp = boost::asio::ip::tcp;

class Reader {
private:
    inline static std::shared_ptr<Data> mp_buf { };
    inline static uint64_t              m_expected { };
    inline static std::vector<char>     m_temp { };

public:
    static void read(tcp::socket           *_p_socket,
                     std::shared_ptr<Data>  _p_data) noexcept;

    static void handlerForSize(tcp::socket                     *_p_socket,
                               std::shared_ptr<Data>            _p_data,
                               const boost::system::error_code &_error,
                               size_t                           _bytes_t) noexcept;
    static void handlerForType(tcp::socket                     *_p_socket,
                               std::shared_ptr<Data>            _p_data,
                               const boost::system::error_code &_error,
                               size_t                           _bytes_t) noexcept;
    static void handlerForData(tcp::socket                     *_p_socket,
                               std::shared_ptr<Data>            _p_data,
                               const boost::system::error_code &_error,
                               size_t                           _bytes_t) noexcept;
};

#endif
