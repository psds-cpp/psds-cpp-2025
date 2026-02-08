#include <iostream>

void PrintArray(const int* begin, const int* end, const int count = 0) {
    if (!begin || !end || begin == end || count < 0) {
        std::cout << "[]\n";
        return;
    }

    // Определяем направление: 1 для движения вперед, -1 для движения назад
    const int step = (begin < end) ? 1 : -1;
    
    // Вычисляем количество элементов (всегда положительное)
    const int total_elements = (step == 1) ? (end - begin) : (begin - end);

    std::cout << "[";
    for (int i = 0; i < total_elements; ++i) {
        // Вычисляем текущий указатель на основе индекса и шага
        const int* ptr = begin + (i * step);

        // Логика переноса строки (count)
        if (count > 0 && i > 0 && i % count == 0) {
            std::cout << "...\n ";
        }

        std::cout << *ptr;

        // Запятая, если это не последний элемент
        if (i < total_elements - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]\n";
}