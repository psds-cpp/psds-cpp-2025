#include <cstddef>
#include <stdexcept>


void PrintBits(long long value, size_t bytes) {
    // Проверка допустимого диапазона размера
    if (bytes == 0 || bytes > 8) {
        return;
    }
    
    // Выводим префикс "0b"
    printf("0b");
    
    // Проходим по всем битам от старшего к младшему
    for (int i = static_cast<int>(bytes * 8) - 1; i >= 0; i--) {
        // Получаем i-тый бит
        if (value & (1LL << i)) {
            printf("1");
        } else {
            printf("0");
        }
        
        // Добавляем апостроф каждые 8 бит (кроме последней группы)
        if (i > 0 && i % 8 == 0) {
            printf("'");
        }
    }
    
    // Перевод строки в конце
    printf("\n");
}
