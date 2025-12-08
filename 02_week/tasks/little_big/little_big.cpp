#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <cstring>

void PrintByte(unsigned char byte) {
    std::cout << std::setw(2) << static_cast<int>(byte);
}

void PrintMemory(int value, bool reverse = false) {
    const size_t size = sizeof(int);
    unsigned char bytes[size];

    std::memcpy(bytes, &value, size);
    std::cout << "0x" << std::hex << std::uppercase << std::setfill('0');

    if (reverse)
        for (size_t i = size; i > 0; --i)
            PrintByte(bytes[i-1]);
    else
        for (size_t i = 0; i < size; ++i)
            PrintByte(bytes[i]);

    std::cout << std::endl;
}

void PrintMemory(double value, bool reverse = false) {
    const size_t size = sizeof(double);
    unsigned char bytes[size];
    
    std::memcpy(bytes, &value, size);
    std::cout << "0x" << std::hex << std::uppercase << std::setfill('0');

    if (reverse)
        for (size_t i = size; i > 0; --i)
            PrintByte(bytes[i-1]);
    else
        for (size_t i = 0; i < size; ++i)
            PrintByte(bytes[i]);

    std::cout << std::endl;
}