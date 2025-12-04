#include <stdexcept>
#include <iostream>
#include <string>


void PrintArray(const int* begin, const int* end, unsigned int limiter = 0) {
    std::string numbers = "[";
    if (begin == nullptr || end == nullptr){
        numbers+="]";
        std::cout << numbers << std::endl;
        return;
    }
    unsigned int i = 0; // счетчик символов для использования ограничителя длины
    int dist = end - begin;
    if (dist > 0) { // ЗАпись слева направо
        while (begin < end){
            int num = *begin;
            std::string reverse_number = "";
            while (num / 10 != 0) { // // Конвертация int в str и запись в массив numbers
                reverse_number += '0' + (num % 10);
                num /= 10;
            }
            reverse_number += '0' + num % 10;
            // Переворачиваем string number
            std::string number;
            for (int j = reverse_number.length() - 1; j >=0; --j) {
                number += reverse_number[j];
            }
            numbers += number;
            if (end - begin == 1) break; // ПРоверка последний ли это символ?
            numbers += ", "; // Если не последний то добавляем ", "
            ++i; // Если счетчик равен ограничителю, то добавляем "... "
            if (limiter != 0 && i == limiter){
                numbers += "...\n ";
                i = 0;
            }
            ++begin;
        }
    }
    else if (dist < 0) { // ЗАпись справо налево
        while (begin > end){
            int num = *begin;
            std::string reverse_number = "";
            while (num / 10 != 0) { // // Конвертация int в str и запись в массив numbers
                reverse_number += '0' + (num % 10);
                num /= 10;
            }
            reverse_number += '0' + num % 10;
            // Переворачиваем string number
            std::string number;
            for (int j = reverse_number.length() - 1; j >=0; --j) {
                number += reverse_number[j];
            }
            numbers += number;
            if (begin - end == 1) break; // ПРоверка последний ли это символ?
            numbers += ", "; // Если не последний то добавляем ", "
            ++i; // Если счетчик равен ограничителю, то добавляем "... "
            if (limiter != 0 && i == limiter){
                numbers += "...\n ";
                i = 0;
            }
            --begin;
        }
    }
    numbers += "]";
    std::cout << numbers << std::endl;
}
