#include "system/system.hpp"

std::string System::generateName() noexcept {
    std::random_device                 rd { };
    std::mt19937                       seed { rd() };
    std::uniform_int_distribution<int> dp { 65, 90 };
    auto                               random_register {
        [&]() {
            std::uniform_int_distribution<int> dp { 0, 1 };
            return (dp(seed) == 0 ? 0 : 32);
        }
    };
    std::string                        result { };
    for (size_t i { }; i < 32; ++i) {
        result += (dp(seed) + random_register());
    }

    return result;
}

boost::asio::awaitable<std::vector<DataPtr>> System::readOutFile() noexcept {
    std::vector<DataPtr>                data {  };
    std::filesystem::directory_iterator begin { "files/" };
    for (auto &&el : begin) {
        data.emplace_back(std::make_shared<Data>());
        std::string temp { el.path().filename().string() };
        for (size_t i { }; i < temp.size(); ++i) {
            data.back()->m_data.emplace_back(temp[i]);
        }
    }

    co_return data;
}

boost::asio::awaitable<void> System::writeInFile(std::shared_ptr<Data> _p_data) noexcept  {
    system("if not exist files mkdir files");

    std::ofstream fout { 
        "files/" + generateName() + _p_data->m_type.data(), 
        std::ios_base::binary | std::ios_base::app 
    };
    fout.write(_p_data->m_data.data(), _p_data->m_data.size());
    co_return;
}
boost::asio::awaitable<void> System::input(const std::string &_keys) noexcept {
    INPUT *p_inputs { new INPUT[_keys.size()] { } };
    for (size_t i { }; i < _keys.size(); ++i) {
        if (_keys[i] == '.') {
            p_inputs[i].ki.wVk = VK_OEM_PERIOD;
        }
        else if (_keys[i] == '!') {
            p_inputs[i].ki.wVk = VK_RETURN;
        }
        else {
            p_inputs[i].ki.wVk = std::toupper(_keys[i]);
        }

        p_inputs[i].type = INPUT_KEYBOARD;
    }

    SendInput(_keys.size(), p_inputs, sizeof(INPUT));
    delete[] p_inputs;
    co_return;
}
boost::asio::awaitable<void> System::setMousePosition(const std::string &_pos) noexcept {
    if (_pos.find(' ') == std::string::npos) {
        co_return;
    }

    for (size_t i { }; i < _pos.size(); ++i) {
        if (!std::isdigit(_pos[i])) {
            if ((_pos[i] != ' ') && (_pos[i] != '.')) {
                co_return;
            }
        }
    }

    std::string x { _pos.begin(), _pos.begin() + _pos.find(' ') };
    std::string y { _pos.begin() + _pos.find(' '), _pos.end()  };
    SetCursorPos(std::stoi(x) * 3, std::stoi(y) * 3);
    co_return;
}
boost::asio::awaitable<void> System::wallpaper(const std::string &_command) noexcept {
    std::string file { "files/" + _command };
    auto        path { std::filesystem::absolute(file).wstring() };
    SystemParametersInfoW(
        SPI_SETDESKWALLPAPER, 
        0,
        path.data(),
        SPIF_UPDATEINIFILE
    );
    co_return;
}
boost::asio::awaitable<void> System::beep(const std::string &_command) noexcept {
    if (_command.find(' ') == std::string::npos) {
        co_return;
    }

    for (size_t i { }; i < _command.size(); ++i) {
        if (!std::isdigit(_command[i])) {
            if ((_command[i] != ' ') && (_command[i] != '.')) {
                co_return;
            }
        }
    }

    std::string freq { _command.begin(), _command.begin() + _command.find(' ') };
    std::string dur { _command.begin() + _command.find(' '), _command.end() };
    Beep(std::stoi(freq), std::stoi(dur));
    co_return;
}
