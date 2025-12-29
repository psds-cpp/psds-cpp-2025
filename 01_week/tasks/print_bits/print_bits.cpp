#include <stddef.h>
#include <iostream>


void PrintBits(long long value, size_t bytes) {
    size_t bits = bytes * 8;
    unsigned long long bit_index = 1ll << (bits - 1);  // 0b1000'...'0000
    size_t delims = 1 + 2 * (bytes - 1);
    // Выделяем буфер под биты, апострофы и '\0' в конце
    size_t buffer_size = bits + delims + 1;

    std::cout << "0b";
    for (size_t i = 0; i < buffer_size - 1; ++i) {
        if (i % 5 == 4) {
            std::cout << '\'';
        } else {
            std::cout << static_cast<char>(static_cast<bool>(value & bit_index) + '0');
            bit_index = bit_index >> 1;
        }
    }
    std::cout << std::endl;
}
