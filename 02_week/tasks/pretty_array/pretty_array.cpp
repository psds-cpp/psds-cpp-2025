#include <stdexcept>
#include <iostream>
#include <string>


void PrintArray(const int* begin, const int* end, unsigned int limiter = 0) {
    std::string numbers = "[";
    int dist = end - begin;
    unsigned int count = 0;
    if (begin == nullptr || end == nullptr || (dist*dist) == 0){ // Проверка на nullptr или пустой массив
        numbers+="]";
        std::cout << numbers << std::endl;
        return;
    }

    while (true){
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
        if (dist*dist == 1) break; // ПРоверка последний ли это символ?
        numbers += ", "; // Если не последний то добавляем ", "
        ++count; // Если счетчик равен ограничителю, то добавляем "... "
        if (limiter != 0 && count == limiter){
            numbers += "...\n ";
            count = 0;
        }
        (dist > 0) ? ++begin : --begin;
        dist = end - begin;
    }
    numbers += "]";
    std::cout << numbers << std::endl;
}
