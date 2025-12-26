#include <cstddef>
#include <stdexcept>
#include <iostream>


void PrintBits(long long value, size_t bytes) {
    std::string result = "0b";
    size_t total_bits = bytes * 8;
    long long mask = 0LL;
    // Тут надо int, иначе условие бесконечное, потому что будет
    // происходит переполнение счетчика
    for (int i = total_bits - 1; i >= 0; --i) {
        mask = 1LL << i;
    
        if (value & mask) result += '1';
        else result += '0';

        if (i % 4 == 0 && i != 0) result += '\'';
    }
    std::cout << result << "\n";
}
