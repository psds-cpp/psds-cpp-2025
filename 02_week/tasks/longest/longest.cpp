#include <stdexcept>

char* FindLongestSubsequence(char* begin, char* end, size_t& count) {
    if (begin == nullptr || end == nullptr || begin > end ||begin == end) {
        count = 0;
        return nullptr;
    }
    
    char* current_start = begin;     // Начало текущей последовательности
    char* longest_start = begin;     // Начало самой длинной последовательности
    size_t current_length = 1;       // Длина текущей последовательности
    size_t max_length = 1;           // Максимальная длина найденной последовательности
    
    // Проходим по всем элементам, начиная со второго
    for (char* it = begin + 1; it != end; ++it) {
        if (*it == *(it - 1)) {
            current_length++;
        } else {
            if (current_length > max_length) {
                max_length = current_length;
                longest_start = current_start;
            }
            current_start = it;
            current_length = 1;
        }
    }
    
    if (current_length > max_length) {
        max_length = current_length;
        longest_start = current_start;
    }
    
    count = max_length;
    return longest_start;
}

const char* FindLongestSubsequence(const char* begin, const char* end, size_t& count) {
    char* result = FindLongestSubsequence(const_cast<char*>(begin), const_cast<char*>(end), count);
    return result;
}