#include <iostream>

void PrintBits(long long value, size_t bytes) {
    if (bytes == 0 || bytes > 8) {
        return;
    }
    
    const size_t total_bits = bytes * 8;
    unsigned long long unsigned_value = value;
    
    std::cout << "0b";
    
    for (size_t i = 0; i < total_bits; ++i) {
        size_t bit_pos = total_bits - 1 - i;
        unsigned long long mask = 1ULL << bit_pos;
        
        if (unsigned_value & mask) {
            std::cout << '1';
        } else {
            std::cout << '0';
        }
        
        if ((i + 1) % 4 == 0 && i != total_bits - 1) {
            std::cout << "'";
        }
    }
    
    std::cout << '\n';
}