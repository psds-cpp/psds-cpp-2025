#include <cstddef>
#include <stdexcept>
#include <iostream>


void PrintBits(long long value, size_t bytes) {
    if (bytes <= 0 || bytes > 8) {
        return;
    }
    size_t size = (bytes * 8) + (bytes * 2 - 1) + 4; //размер массива под число включая (bytes * 8) цифр, (bytes * 2 - 1) символов ' после каждой 4 цифры, 3 символа: 0, b, \0 и \n
    char bit_num[size];
    bit_num[0] = '0';
    bit_num[1] = 'b';
    bit_num[size - 1] = '\0';
    bit_num[size - 2] = '\n';
    for (size_t i = size - 3, comma_position = 1; i > 1; --i) {
        if (comma_position % 5 == 0) { // добавление знака ' после каждых 4 цифр
            bit_num[i] = '\'';
            ++comma_position;
            continue;
        }
        char symbol = '0' + (value & 1);
        bit_num[i] = symbol;
        value = value >> 1;

        ++comma_position;
    }
    std::cout << bit_num;
}
