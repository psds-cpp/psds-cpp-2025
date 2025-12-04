#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <cstring>

void PrintMemory(int value, bool reverseBytes = false) {
    unsigned int temp;
    std::memcpy(&temp, &value, sizeof(value));
    
    if (!reverseBytes) {
        // Little-endian порядок (по умолчанию)
        std::cout << "0x";
        for (int i = 0; i < static_cast<int>(sizeof(temp)); i++) {
            unsigned char byte = (temp >> (i * 8)) & 0xFF;
            std::cout << std::hex << std::setw(2) << std::setfill('0') 
                      << static_cast<unsigned int>(byte);
        }
    } else {
        // Big-endian порядок (инвертированный)
        std::cout << "0x";
        for (int i = static_cast<int>(sizeof(temp)) - 1; i >= 0; i--) {
            unsigned char byte = (temp >> (i * 8)) & 0xFF;
            std::cout << std::hex << std::setw(2) << std::setfill('0') 
                      << static_cast<unsigned int>(byte);
        }
    }
    std::cout << std::dec << "\n";
}

void PrintMemory(double value, bool reverseBytes = false) {
    unsigned long long temp;
    std::memcpy(&temp, &value, sizeof(value));
    
    if (!reverseBytes) {
        // Little-endian порядок (по умолчанию)
        std::cout << "0x";
        for (int i = 0; i < static_cast<int>(sizeof(temp)); i++) {
            unsigned char byte = (temp >> (i * 8)) & 0xFF;
            std::cout << std::hex << std::setw(2) << std::setfill('0') 
                      << static_cast<unsigned int>(byte);
        }
    } else {
        // Big-endian порядок (инвертированный)
        std::cout << "0x";
        for (int i = static_cast<int>(sizeof(temp)) - 1; i >= 0; i--) {
            unsigned char byte = (temp >> (i * 8)) & 0xFF;
            std::cout << std::hex << std::setw(2) << std::setfill('0') 
                      << static_cast<unsigned int>(byte);
        }
    }
    std::cout << std::dec << "\n";
}