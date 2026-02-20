#include <iostream>
#include <stdexcept>

void PrintArray(const int* begin, const int* end, size_t limit = 0) {
    // Если указатели равны nullptr, выводим пустой массив
    if (begin == nullptr && end == nullptr) {
        std::cout << "[]\n";
        return;
    }
    
    // Если диапазон пустой
    if (begin == end) {
        std::cout << "[]\n";
        return;
    }
    
    bool reverse = false;
    const int* current = begin;
    const int* last = end;
    
    // Определяем направление обхода
    if (end < begin) {
        reverse = true;
        // Для обратного порядка: begin должен быть "после" end в массиве
        // Меняем местами указатели для упрощения логики
        current = end + 1;  // end указывает "за конец" в обратном порядке
        last = begin + 1;   // begin указывает "на начало" в обратном порядке
    }
    
    std::cout << "[";
    
    size_t elements_in_current_line = 0;
    size_t total_elements = 0;
    
    // Подсчитываем общее количество элементов
    if (!reverse) {
        total_elements = end - begin;
    } else {
        total_elements = begin - end;
    }
    
    // Выводим элементы
    while (true) {
        // Выводим текущий элемент
        if (!reverse) {
            std::cout << *current;
        } else {
            std::cout << *(last - 1);
        }
        
        elements_in_current_line++;
        total_elements--;
        
        // Проверяем, нужно ли переходить на новую строку
        if (limit > 0 && elements_in_current_line >= limit && total_elements > 0) {
            std::cout << ", ...\n ";
            elements_in_current_line = 0;
        }
        // Проверяем, последний ли это элемент
        else if (total_elements == 0) {
            std::cout << "]";
            break;
        }
        // Иначе выводим запятую и пробел
        else {
            std::cout << ", ";
        }
        
        // Переходим к следующему элементу
        if (!reverse) {
            current++;
            if (current >= end) break;
        } else {
            last--;
            if (last <= end) break;
        }
    }
    
    std::cout << "\n";
}