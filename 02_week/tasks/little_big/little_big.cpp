#include <iostream>
#include <cstring>
#include <cstdint>

void PrintMemory(int value, bool is_big_endian = false) {
    char digits[8 + 1];

    std::memset(digits, '0', sizeof(digits));

    for (size_t i = 0; i < 4; ++i) {
        uint8_t byte = *(reinterpret_cast<uint8_t*>(&value) + i);

        for (size_t j = 0; j < 2; ++j) {
            uint8_t code = (byte & (0b1111 << (j * 4))) >> (j * 4);

            char ch = (code < 10) ? '0' + code : 'A' + code - 10;

            if (is_big_endian) {
                digits[i * 2 + j] = ch;
            }
            else {
                digits[(3 - i) * 2 + j] = ch;
            }
        }
    }

    digits[8] = '\0';

    std::cout << "0x";

    for (int i = 7; i >= 0; --i) {
        std::cout << digits[i];
    }

    std::cout << '\n';
}

void PrintMemory(double value, bool is_big_endian = false) {
    char digits[16 + 1];

    std::memset(digits, '0', sizeof(digits));

    for (size_t i = 0; i < 8; ++i) {
        uint8_t byte = *(reinterpret_cast<uint8_t*>(&value) + i);

        for (size_t j = 0; j < 2; ++j) {
            uint8_t code = (byte & (0b1111 << (j * 4))) >> (j * 4);

            char ch = (code < 10) ? '0' + code : 'A' + code - 10;

            if (is_big_endian) {
                digits[i * 2 + j] = ch;
            }
            else {
                digits[(7 - i) * 2 + j] = ch;
            }
        }
    }

    digits[16] = '\0';

    std::cout << "0x";

    for (int i = 15; i >= 0; --i) {
        std::cout << digits[i];
    }

    std::cout << '\n';
}