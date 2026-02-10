#include <iostream>
#include <algorithm>

void PrintBits(long long value, size_t bytes) {
    auto count_bits = bytes * 8;
    std::string str_bset = "0b";

    for (size_t i = count_bits; i > 0; --i) {
        auto b_i = (value >> (i - 1)) & 1u;
        b_i ? str_bset += "1" : str_bset += "0";

        if ((i - 1) % 4 == 0 && i != count_bits && i != 1) {
            str_bset += '\'';
        }
    }    
    std::cout << str_bset << "\n";
}
