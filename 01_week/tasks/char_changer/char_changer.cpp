#include <cstddef>
#include <stdexcept>
#include <cctype>

size_t CharChanger(char array[], size_t size, char delimiter = ' ') {
    if (size == 0) return 0;                      
    
    size_t pos_read = 0;    // позиция чтения     
    size_t pos_write = 0;   // позиция записи
    
    while (array[pos_read] != '\0') { // проверка на последний символ
        char current_char = array[pos_read]; // изменяемый символ
        size_t count = 1;

        while (pos_read + count < size && array[pos_read + count] == current_char) { // подсчет повторающихся символов
            ++count;
        }

        if (isdigit(current_char)) {// проверка на цифры
            current_char = '*';
        }
        else if (islower(current_char)) { // проверка на строчные буквы
            current_char = toupper(current_char);
        }
        else if (!isupper(current_char) && current_char != ' ') { //остальные символы, кроме пробелов и прописных букв
            current_char = '_';
        }

        if (current_char == ' ') { // оработка пробелов
            current_char = delimiter;
            if (pos_write < size) {
                array[pos_write] = current_char;
                ++pos_write;
            }
        }

        else { // обработка остальных символов
            if (pos_write < size) { //записываем символ
                array[pos_write] = current_char;
                ++pos_write;
            }
            if ( count > 1) { ///обрабатываем повторения
                if (count >= 10) {
                    if (pos_write < size) {
                        array[pos_write] = '0';
                        ++pos_write;
                    }
                }
                else {
                    if (pos_write < size) {
                        array[pos_write] = '0' + count;
                        ++pos_write;
                    }
                }
            }
        }
        pos_read += count;
    }
            
    

        // Добавляем завершающий нуль-символ
    if (pos_write < size) {
        array[pos_write] = '\0';
    }
    else if (size > 0) {
        array[size - 1] = '\0';
        pos_write = size - 1;
    }

    return pos_write;
}
