#include <iostream>
#include <iomanip>
#include <stdexcept>

void PrintMemory(int value, bool reverse = false) {// Для int
    unsigned char* bytes = reinterpret_cast<unsigned char*>(&value);
    std::cout << "0x" << std::uppercase;
    if (reverse) {
        for (size_t i = sizeof(int); i > 0; --i) {
            std::cout << std::hex << std::setw(2) << std::setfill('0')
                      << static_cast<int>(bytes[i - 1]); }
    } else {
        for (size_t i = 0; i < sizeof(int); ++i) {
            std::cout << std::hex << std::setw(2) << std::setfill('0')
                      << static_cast<int>(bytes[i]); }
    }
    std::cout << std::dec << std::endl;
}

void PrintMemory(double value, bool reverse = false) {// Для double
    unsigned char* bytes = reinterpret_cast<unsigned char*>(&value);
    std::cout << "0x" << std::uppercase;
    if (reverse) {
        for (size_t i = sizeof(double); i > 0; --i) {
            std::cout << std::hex << std::setw(2) << std::setfill('0')
                      << static_cast<int>(bytes[i - 1]); }
    } else {
        for (size_t i = 0; i < sizeof(double); ++i) {
            std::cout << std::hex << std::setw(2) << std::setfill('0')
                      << static_cast<int>(bytes[i]); }
    }
    std::cout << std::dec << std::endl;
}

