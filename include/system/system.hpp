#ifndef SYSTEM_SYSTEM_HPP
#define SYSTEM_SYSTEM_HPP

#include "libs.hpp"

class System {
private:
    static std::string generateName() noexcept;

public:
    static boost::asio::awaitable<std::vector<DataPtr>> readOutFile() noexcept;

    static boost::asio::awaitable<void> command(const std::string &_command) noexcept {
        system(_command.c_str());
        co_return;
    }
    static boost::asio::awaitable<void> writeInFile(std::shared_ptr<Data> _p_data) noexcept;
    static boost::asio::awaitable<void> input(const std::string &_keys) noexcept;
    static boost::asio::awaitable<void> setMousePosition(const std::string &_pos) noexcept;
    static boost::asio::awaitable<void> wallpaper(const std::string &_command) noexcept;
    static boost::asio::awaitable<void> beep(const std::string &_command) noexcept;
};

#endif
