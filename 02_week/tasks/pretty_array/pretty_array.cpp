#include <iostream>


void PrintArray(const int* begin, const int* end, const int threshold = 0) {
    if (!begin || !end) {
        std::cout << "[]\n";
        return;
    }

    std::cout << "[";
    for (
        const int* ptr = begin;
        begin < end ? ptr < end : ptr > end;
        begin < end ? ++ptr : --ptr
    ) {
        if (threshold && static_cast<int>(ptr - begin) % threshold == 0 && ptr != begin) {
            std::cout << "...\n ";
        }

        std::cout << *ptr;

        if (ptr != (begin < end ? end - 1 : end + 1)) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}