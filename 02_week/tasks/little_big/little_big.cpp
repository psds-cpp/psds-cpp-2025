#include <iostream>
#include <cstddef>
#include <iomanip>

void PrintHex(const unsigned char* ptr, const size_t size, bool inverse) {
    for (size_t i = 0; i < size; ++i) {
        std::cout << std::uppercase << std::hex << std::setw(2) << std::setfill('0') 
                  << (!inverse ? static_cast<unsigned int>(ptr[i]) : static_cast<unsigned int>(ptr[size - 1 - i]));
    }
}

void PrintMemory(int num, bool inverse = false) {
    const size_t size = sizeof(int);
    auto ptr = reinterpret_cast<const unsigned char*>(&num);
    
    std::cout << "0x";
    PrintHex(ptr, size, inverse);
    std::cout << std::endl;
}

void PrintMemory(double num, bool inverse = false) {
    const size_t size = sizeof(double);
    auto ptr = reinterpret_cast<const unsigned char*>(&num);
    
    std::cout << "0x";
    PrintHex(ptr, size, inverse);
    std::cout << std::endl;
}