#include <iostream>

/*Представление числа в памяти*/

void PrintMemory(int value, bool reverse = true) {

    // Определение порядка байт
    const unsigned char* bytes = reinterpret_cast<const unsigned char*>(&value);
    
    // Вывод префикса 0x
    std::cout << "0x";
    
    if (reverse) {
        // Обратный порядок (big-endian) - от старшего байта к младшему
        for (int i = sizeof(value) - 1; i >= 0; --i) {
            printf("%02X", bytes[i]);
        }
    } else {
        // Прямой порядок (little-endian) - от младшего байта к старшему
        for (size_t i = 0; i < sizeof(value); ++i) {
            printf("%02X", bytes[i]);
        }
    }
    // Перевод строки
    std::cout << std::endl;
}

void PrintMemory(double value, bool reverse = true) {

    // Определение порядка байт
    const unsigned char* bytes = reinterpret_cast<const unsigned char*>(&value);
    
    // Вывод префикса 0x
    std::cout << "0x";
    
    if (reverse) {
        // Обратный порядок (big-endian) - от старшего байта к младшему
        for (int i = sizeof(value) - 1; i >= 0; --i) {
            printf("%02X", bytes[i]);
        }
    } else {
        // Прямой порядок (little-endian) - от младшего байта к старшему
        for (size_t i = 0; i < sizeof(value); ++i) {
            printf("%02X", bytes[i]);
        }
    }
    // Перевод строки
    std::cout << std::endl;
}