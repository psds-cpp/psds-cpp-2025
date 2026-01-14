#include <cstddef>
#include <stdexcept>
#include <iostream>

size_t CharChanger(char array[], size_t size, char delimiter = ' ') {
    size_t position = 0;
    char current;
    char next;
    unsigned int n_repited_char = 1;
    bool is_char_repited = false;
    for (size_t i = 0; i < size-1; ++i) {
        current = array[i];
        next = array[i+1];
        if (next == current) { // замена повторяющихся символов
            ++n_repited_char;
            is_char_repited = true;
            continue;
        }
        if (ispunct(current)) { //проверка на другие символы
            array[position] = '_';
        }
        if (isdigit(current)) { // проверка на цифру
            array[position] = '*';
        }
        if (islower(current)) { //проверка на пропись
            array[position] = current - 32;
        }
        if (isupper(current)) { //проверка на пропись
            array[position] = current;
        }
        if (isspace(current)) { //проверка единичного символа на пробел
            array[position] = delimiter;
        }

        if (is_char_repited) { // учет повторений
            if (isspace(current)) { // при пробеле
                array[position] = delimiter;
            }
            else { // при символе
                ++position;
                array[position] = (n_repited_char < 10) ? ('0' + n_repited_char) : '0';
            }
            is_char_repited = false;
            n_repited_char = 1;
        }
        ++position;
    }
    array[position] = '\0';
    return position;
}
