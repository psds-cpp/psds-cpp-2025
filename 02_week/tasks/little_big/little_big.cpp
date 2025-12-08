#include <iostream>

/*Представление числа в памяти*/

void PrintMemory(int value, bool reverse = true) {

    // Оперделение порядока байт
    const unsigned char* bytes = reinterpret_cast<const unsigned char*>(&value);
    
    if (reverse) {
        // Обратный порядок (little-endian)
        for (int i = sizeof(value) - 1; i >= 0; --i) {
            printf("%02X", bytes[i]);
            if (i > 0) printf(" ");
        }
    } else {
        // Прямой порядок (big-endian)
        for (size_t i = 0; i < sizeof(value); ++i) {
            printf("%02X", bytes[i]);
            if (i < sizeof(value) - 1) printf(" ");
        }
    }
    printf("\n");
}

void PrintMemory(double value, bool reverse = true) {

    // Оперделение порядока байт
    const unsigned char* bytes = reinterpret_cast<const unsigned char*>(&value);
    
    if (reverse) {
        // Обратный порядок (little-endian)
        for (int i = sizeof(value) - 1; i >= 0; --i) {
            printf("%02X", bytes[i]);
            if (i > 0) printf(" ");
        }
    } else {
        // Прямой порядок (big-endian)
        for (size_t i = 0; i < sizeof(value); ++i) {
            printf("%02X", bytes[i]);
            if (i < sizeof(value) - 1) printf(" ");
        }
    }
    printf("\n");
}