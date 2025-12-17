#include <stdexcept>
#include <cstring>
#include <iostream>
#include <cstdint>
#include <iomanip>

void PrintMemory(int value, bool reverse = false) {
    uint32_t bytes;
    std::memcpy(&bytes, &value, sizeof(value));
    
    if (reverse) {
        // Оригинальный порядок байт (big-endian представление)
        std::cout << "0x" << std::uppercase << std::hex << std::setfill('0') << std::setw(8) 
                  << bytes << "\n";
    } else {
        // Little-endian представление (байты в обратном порядке)
        uint32_t reversed = 0;
        for (size_t i = 0; i < sizeof(value); ++i) {
            reversed = (reversed << 8) | ((bytes >> (i * 8)) & 0xFF);
        }
        std::cout << "0x" << std::uppercase << std::hex << std::setfill('0') << std::setw(8) 
                  << reversed << "\n";
    }
}

void PrintMemory(double value, bool reverse = false) {
    uint64_t bytes;
    std::memcpy(&bytes, &value, sizeof(value));
    
    if (reverse) {
        // Оригинальный порядок байт (big-endian представление)
        std::cout << "0x" << std::uppercase << std::hex << std::setfill('0') << std::setw(16) 
                  << bytes << "\n";
    } else {
        // Little-endian представление (байты в обратном порядке)
        uint64_t reversed = 0;
        for (size_t i = 0; i < sizeof(value); ++i) {
            reversed = (reversed << 8) | ((bytes >> (i * 8)) & 0xFF);
        }
        std::cout << "0x" << std::uppercase << std::hex << std::setfill('0') << std::setw(16) 
                  << reversed << "\n";
    }
}
