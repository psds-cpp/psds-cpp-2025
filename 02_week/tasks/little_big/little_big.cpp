#include <iostream>
#include <iomanip>
#include <cstring>

void PrintMemory(int value, bool invert = false) {
    //memcpy копирует байты из числа в массив
    unsigned char bytes[sizeof(int)];
    std::memcpy(bytes, &value, sizeof(int));
    
    std::cout << "0x" << std::uppercase << std::hex;
    
    if (!invert) {
        for (size_t i = 0; i < sizeof(int); ++i) {
            unsigned int byte_value = bytes[i];
            std::cout << std::setw(2) << std::setfill('0') << byte_value;
        }
    } else {
        for (int i = sizeof(int) - 1; i >= 0; --i) {
            unsigned int byte_value = bytes[i];
            std::cout << std::setw(2) << std::setfill('0') << byte_value;
        }
    }
    
    std::cout << std::endl;
}

void PrintMemory(double value, bool invert = false) {
    unsigned char bytes[sizeof(double)];
    std::memcpy(bytes, &value, sizeof(double));
    
    std::cout << "0x" << std::uppercase << std::hex;
    
    if (!invert) {
        for (size_t i = 0; i < sizeof(double); ++i) {
            unsigned int byte_value = bytes[i];
            std::cout << std::setw(2) << std::setfill('0') << byte_value;
        }
    } else {
        for (int i = sizeof(double) - 1; i >= 0; --i) {
            unsigned int byte_value = bytes[i];
            std::cout << std::setw(2) << std::setfill('0') << byte_value;
        }
    }
    
    std::cout << std::endl;
}