#include <iostream>
#include "network/acceptor.hpp"

int main() {
    setlocale(0, "");

    boost::asio::io_context io_context { };
    Acceptor                acceptor { io_context };
    acceptor.start();
    io_context.run();
}
