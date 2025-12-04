#include <cstddef>
#include <stdexcept>


size_t CharChanger(char array[], size_t size, char delimiter = ' ') {
    if (array == nullptr || size == 0) {
        return 0;
    }
    
    size_t read = 0;    // позиция чтения
    size_t write = 0;   // позиция записи
    
    while (read < size && array[read] != '\0') {
        char c = array[read];
        char new_char;
        
        // Преобразуем символ по правилам
        if (c >= '0' && c <= '9') {
            new_char = '*';
        } else if (c >= 'a' && c <= 'z') {
            new_char = c - 'a' + 'A';  // строчная -> прописная
        } else if (c >= 'A' && c <= 'Z') {
            new_char = c;
        } else if (c == ' ') {
            new_char = delimiter;
        } else {
            new_char = '_';
        }
        
        // Считаем количество одинаковых символов
        size_t count = 1;
        size_t next = read + 1;
        while (next < size && array[next] != '\0') {
            char next_c = array[next];
            char next_new_char;
            
            if (next_c >= '0' && next_c <= '9') {
                next_new_char = '*';
            } else if (next_c >= 'a' && next_c <= 'z') {
                next_new_char = next_c - 'a' + 'A';
            } else if (next_c >= 'A' && next_c <= 'Z') {
                next_new_char = next_c;
            } else if (next_c == ' ') {
                next_new_char = delimiter;
            } else {
                next_new_char = '_';
            }
            
            if (next_new_char == new_char) {
                count++;
                next++;
            } else {
                break;
            }
        }
        
        // Записываем результат
        if (new_char == delimiter) {
            // Для разделителя пишем только один символ
            if (write < size - 1) {
                array[write++] = new_char;
            }
        } else if (count >= 10) {
            // 10+ повторений: символ + '0'
            if (write < size - 2) {
                array[write++] = new_char;
                array[write++] = '0';
            }
        } else if (count > 1) {
            // 2-9 повторений: символ + цифра
            if (write < size - 2) {
                array[write++] = new_char;
                array[write++] = '0' + count;
            }
        } else {
            // 1 повторение: только символ
            if (write < size - 1) {
                array[write++] = new_char;
            }
        }
        
        read = next;  // переходим к следующей группе символов
    }
    
    // Завершаем строку
    if (write < size) {
        array[write] = '\0';
    } else if (size > 0) {
        array[size - 1] = '\0';
    }
    
    return write + 1;  // позиция после '\0'
}