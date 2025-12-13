#include <stdexcept>
#include <iostream>

void PrintArray(const int* begin, const int* end, size_t limit = 0) {
    const bool reverse = (begin > end);
    const size_t len = std::abs(end - begin);

    if (len == 0) {
        std::cout << "[]\n";
        return;
    }

    const int* cur = begin;
    size_t cnt = 0;
    
    std::cout << "[";

    for (size_t i = 0; i < len; ++i) {
        std::cout << *cur; 
        if (i != len - 1) {
            if ((limit > 0) && (cnt == limit - 1)) {
                std::cout << ", ...\n ";
                cnt = 0;
            } 
            else {
                std::cout << ", ";
                ++cnt;
            }
        }
        
        if (i != len - 1)
            cur = reverse ? cur - 1 : cur + 1;
    }
    std::cout << "]\n";
}