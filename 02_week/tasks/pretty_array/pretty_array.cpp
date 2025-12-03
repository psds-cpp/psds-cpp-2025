#include <iostream>


void PrintArray(const int* begin, const int* end, const int threshold = 0) {
    if (!begin || !end) {
        std::cout << "[]\n";
        return;
    }

    std::cout << "[";
    if (begin < end) {
        for (const int* ptr = begin; ptr < end; ++ptr) {
            if (threshold && static_cast<int>(ptr - begin) % threshold == 0 && ptr != begin) {
                std::cout << "...\n ";
            }

            std::cout << *ptr;

            if (ptr != end - 1) {
                std::cout << ", ";
            }
        }
    }
    else {
        for (const int* ptr = begin; ptr > end; --ptr) {
            if (threshold && static_cast<int>(ptr - begin) % threshold == 0 && ptr != begin) {
                std::cout << "...\n ";
            }

            std::cout << *ptr;

            if (ptr != end + 1) {
                std::cout << ", ";
            }
        }
    }
    std::cout << "]" << std::endl;
}