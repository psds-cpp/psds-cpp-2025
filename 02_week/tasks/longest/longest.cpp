#include <stdexcept>
//include <cstdef>

const char* FindLongestSubsequence(const char* begin, const char* end, std::size_t& count) {
    // Проверка на некорректные указатели
    if (!begin || !end || begin > end) {
        count = 0;
        return nullptr;
    }
    
    // Проверка на пустой диапазон
    if (begin == end) {
        count = 0;
        return nullptr;
    }
    
    const char* longest_start = begin;
    const char* current_start = begin;
    std::size_t longest_length = 1;
    std::size_t current_length = 1;
    
    // Проходим по массиву, начиная со второго элемента
    const char* current = begin + 1;
    while (current < end) {
        if (*current == *current_start) {
            // Текущий символ совпадает с началом текущей подпоследовательности
            current_length++;
        } else {
            // Текущий символ отличается, начинаем новую подпоследовательность
            if (current_length > longest_length) {
                longest_length = current_length;
                longest_start = current_start;
            }
            current_start = current;
            current_length = 1;
        }
        current++;
    }
    
    // Проверяем последнюю подпоследовательность
    if (current_length > longest_length) {
        longest_length = current_length;
        longest_start = current_start;
    }
    
    count = longest_length;
    return longest_start;
}

char* FindLongestSubsequence(char* begin, char* end, std::size_t& count) {
    // Перегруженная версия для неконстантных указателей
    const char* result = FindLongestSubsequence(const_cast<const char*>(begin), 
                                                const_cast<const char*>(end), 
                                                count);
    // Конвертируем результат обратно в неконстантный указатель
    return const_cast<char*>(result);
}