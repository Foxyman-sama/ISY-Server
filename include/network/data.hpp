#ifndef NETWORK_DATA_HPP
#define NETWORK_DATA_HPP

#include <vector>

constexpr size_t g_PACKET_SIZE { 65'536 };

class Data {
public:
    std::vector<char> m_data;
    std::vector<char> m_type;
    uint64_t          m_size;
};

#endif
