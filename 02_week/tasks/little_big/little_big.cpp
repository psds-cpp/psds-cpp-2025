#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <cstring>

void PrintByte(unsigned char byte) {
    std::cout << std::setw(2) << static_cast<int>(byte);
}

void PrintBytes(unsigned char bytes[], size_t size, bool reverse) {
    std::cout << "0x" << std::hex << std::uppercase << std::setfill('0');
    for (size_t i = 0; i < size; ++i) {
        size_t index = reverse ? (size - 1 - i) : i;
        PrintByte(bytes[index]);
    }
    std::cout << std::endl;
}

void PrintMemory(int value, bool reverse = false) {
    const size_t size = sizeof(int);
    unsigned char bytes[size];
    std::memcpy(bytes, &value, size);
    PrintBytes(bytes, size, reverse);
}

void PrintMemory(double value, bool reverse = false) {
    const size_t size = sizeof(double);
    unsigned char bytes[size];
    std::memcpy(bytes, &value, size);
    PrintBytes(bytes, size, reverse);
}