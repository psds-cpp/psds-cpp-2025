#include <cstddef>
#include <stdexcept>
#include <bits/stdc++.h>


void PrintBits(long long value, size_t bytes) {
    size_t bits = bytes*8;
    bool reverse = false;
    bool res[bits] = {0};

    if (value < 0) {
        reverse = true;
        value = -value - 1;
    }

    for (size_t i = bits; i > 0 && value != 0; --i) {
        res[i-1] = value % 2;
        value /= 2;
    }

    if (reverse)
        for (size_t i = 0; i < bits; ++i)
            res[i] ^= 1;

    std::cout << "0b";
    for (size_t i = 0; i < bits; ++i) {
        if (i % 4 == 0 && i != 0)
            std::cout << '\'';
        std::cout << res[i];
    }
    std::cout << '\n';
}
