#include <iostream>

void PrintArray(const int* begin, const int* end, size_t limit = 0) {
    if (!begin || !end) {
        std::cout << "[]\n";
        return;
    }

    size_t length = (begin > end) ? (begin - end) : (end - begin);

    std::cout << '[';

    for (size_t i = 0; i < length; ++i) {
        std::cout << ((begin < end) ? begin[i] : end[length - i]);

        if ((i + 1) == length) {
            break;
        }

        std::cout << ", ";

        if ((limit > 0) && ((i + 1) % limit == 0)) {
            std::cout << "...\n ";
        }
    }

    std::cout << "]\n";
}