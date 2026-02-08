#include <iostream>
#include <iomanip>
#include <cstring>
#include <algorithm>


void PrintMemory(int number, bool inversion = false) {
    unsigned char* bytes = reinterpret_cast<unsigned char*>(&number);
    
    std::cout << "0x";
    if (inversion) {
        // Читаем байты в обратном порядке сразу при выводе
        for (size_t i = sizeof(int); i > 0; --i) {
            std::cout << std::hex << std::uppercase 
                      << std::setfill('0') << std::setw(2) 
                      << static_cast<unsigned int>(bytes[i-1]);
        }
    } else {
        for (size_t i = 0; i < sizeof(int); ++i) {
            std::cout << std::hex << std::uppercase 
                      << std::setfill('0') << std::setw(2) 
                      << static_cast<unsigned int>(bytes[i]);
        }
    }
    std::cout << std::dec << std::endl;
}

void PrintMemory(double number, bool inversion = false) {
    unsigned char* bytes = reinterpret_cast<unsigned char*>(&number);
    
    std::cout << "0x";
    if (inversion) {
        // Читаем байты в обратном порядке сразу при выводе
        for (size_t i = sizeof(double); i > 0; --i) {
            std::cout << std::hex << std::uppercase 
                      << std::setfill('0') << std::setw(2) 
                      << static_cast<unsigned int>(bytes[i-1]);
        }
    } else {
        for (size_t i = 0; i < sizeof(double); ++i) {
            std::cout << std::hex << std::uppercase 
                      << std::setfill('0') << std::setw(2) 
                      << static_cast<unsigned int>(bytes[i]);
        }
    }
    std::cout << std::dec << std::endl;
}