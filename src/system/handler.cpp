#include "system/handler.hpp"

void Handler::handler(tcp::socket                     *_p_socket,
                      const boost::system::error_code &_error, 
                      size_t                           _bytes_t) noexcept { 
    if (!_error) {
        if (!strcmp(m_buf.data(), "read")) {
            std::cout << "read\n";
            prepareDataBuffer();
            auto future { Reader::read(_p_socket, mp_data) };
            std::thread { [&]() {
                while (!mp_data->m_size) { 
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
                while (mp_data->m_data.size() != mp_data->m_size) {         
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }

                OUTPUT("Read successful! Size: " << mp_data->m_data.size(), FOREGROUND_GREEN)
            } }.detach();

            std::cout << future.get() << '\n';
        }
    }
    else {
        delete _p_socket;
    }
}
void Handler::prepareDataBuffer() noexcept {
    mp_data->m_size = 0;
    mp_data->m_type.clear();
    mp_data->m_type.resize(5, '\0');
    mp_data->m_data.clear();
}

void Handler::processSocket(tcp::socket *_p_socket) noexcept {
    m_buf.clear();
    m_buf.resize(1024);
    boost::asio::async_read(
        *_p_socket,
         boost::asio::buffer(m_buf),
         boost::asio::transfer_at_least(1),
         boost::bind(
             &Handler::handler,
              _p_socket,
              boost::asio::placeholders::error,
              boost::asio::placeholders::bytes_transferred
         )
    );
}
