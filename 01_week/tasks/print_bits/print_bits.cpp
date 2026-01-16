#include <cstddef>
#include <vector>
#include <iostream>

void PrintBits(long long value, size_t bytes) {
    size_t bitLen = 8 * bytes;
    std::vector<char> bits(bitLen);

    for(size_t i = 0; i < bitLen; ++i){
        bits[bitLen-i-1] = value % 2 == 0 ? '0' : '1';
        value = value >> 1;
    }

    std::cout << "0b";
    for(size_t i = 0; i < bitLen; ++i){
        std::cout << bits[i];
        if((i+1) % 4 == 0 && (i+1) != bitLen){
            std::cout << '\'';
        }
    }
    std::cout << "\n";
}
