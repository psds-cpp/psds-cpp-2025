#include <stdexcept>
#include <iostream>



void PrintArray(const int* begin, const int* end, size_t limit = 0) {
    // Направление
    bool rev = end < begin;
    
    size_t size = 0;
    if (!rev) {
        size = end - begin;
    } else {
        size = begin - end;
    }
    
    if (size == 0) {
        std::cout << "[]" << std::endl;
        return;
    }
    

    std::cout << "[";
    for (size_t i = 0; i < size; ++i) {
        if (!rev) {
            std::cout << begin[i];
        } else {
            std::cout << *(begin - i);
        }
        
        // Ограничитель
        if (i < size - 1) {
            if (limit > 0 && (i + 1) % limit == 0) {
                std::cout << ", ..." << std::endl << " ";
            } else {
                std::cout << ", ";
            }
        }
    }
    
    std::cout << "]" << std::endl;
}