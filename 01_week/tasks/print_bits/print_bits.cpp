#include <cstddef>
#include <stdexcept>
#include <iostream>


void PrintBits(long long value, size_t bytes) {
    if (bytes > 0 && bytes <= 8){
        std::cout << "0b";
        for(size_t i = 0; i < bytes * 8; ++i) {
            std::cout << ((value >> (bytes * 8 - i - 1)) & 1);
            if (i != (bytes * 8 - 1) && (i % 4 == 3) && i != 0)
                std::cout << '\'';
            else if (i == bytes * 8 - 1)
                std::cout << '\n';
        }
    }
}
