#include <iostream>
#include "network/acceptor.hpp"

#ifdef NDEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main() {
    setlocale(0, "");

    boost::asio::io_context io_context { };
    Acceptor                acceptor { io_context };
    boost::asio::co_spawn(io_context, acceptor.start(), boost::asio::detached);
    io_context.run();
}
