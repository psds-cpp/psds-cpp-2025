#include <stdexcept>


// Тип для указателя на функцию-предикат
using Predicate = bool(*)(int);

const int* FindLastElement(const int* begin, const int* end, Predicate predicate) {
    // Проверка на некорректные указатели
    if (begin == nullptr || end == nullptr) {
        return end;
    }
    
    // Проверка на некорректный диапазон (begin > end)
    if (begin > end) {
        return end;
    }
    
    // Указатель для последнего найденного элемента
    const int* last_found = end; // Изначально указывает за последний элемент
    
    // Проходим по массиву с начала до конца
    for (const int* current = begin; current < end; ++current) {
        if (predicate(*current)) {
            last_found = current; // Обновляем указатель на последний найденный элемент
        }
    }
    
    return last_found;
}