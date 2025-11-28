#include <cstddef>
#include <stdexcept>
#include <iostream>


void PrintBits(long long value, size_t bytes) {
    if (bytes == 0 || bytes > 8) {
        return;
    }
    
    std::cout << "0b";
    for (int i = static_cast<int>(bytes * 8 - 1); i >= 0; i--) {
        unsigned long long bit = (static_cast<unsigned long long>(value) >> i) & 1;
        std::cout << bit;
        
        if (i > 0 && i % 4 == 0) {
            std::cout << "'";
        }
    }
    std::cout << std::endl;
}
