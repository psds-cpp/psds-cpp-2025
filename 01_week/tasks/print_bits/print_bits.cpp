#include <cstddef>
#include <iostream>

void PrintBits(long long value, size_t bytes) {
    size_t bitLen = 8 * bytes;

    std::cout << "0b";
    for (size_t i = bitLen - 1; i < bitLen; --i) {
        std::cout << ((value >> i) % 2 == 0 ? '0' : '1');
        if (i != 0 && i % 4 == 0) {
            std::cout << '\'';
        }
    }

    std::cout << "\n";
}
