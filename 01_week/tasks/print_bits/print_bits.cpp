#include <stddef.h>
#include <iostream>


void PrintBits(long long value, size_t bytes) {
    long long bit_index = 1ll;  // 0b0000'...'000

    size_t bits = bytes * 8;
    size_t delims = 1 + 2 * (bytes - 1);

    // Выделяем буфер под биты, апострофы и '\0' в конце
    size_t buffer_size = bits + delims + 1;

    char* buffer = new char[buffer_size] {'\0'};

    for (int i = buffer_size - 2; i >= 0; --i) {
        if (i % 5 == 4) {
            buffer[i] = '\'';
        } else {
            buffer[i] = static_cast<bool>(value & bit_index) + '0';
            bit_index = bit_index << 1;
        }
    }
    
    std::cout << "0b" << buffer << std::endl;

    delete[] buffer;
    buffer = nullptr;
}
