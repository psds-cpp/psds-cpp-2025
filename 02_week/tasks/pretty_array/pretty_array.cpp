#include <iostream>
#include <cstddef>

void PrintArray(const int* begin, const int* end, size_t line_limit = 0) {
    std::cout << "[";
    if (!begin || !end || begin == end) {
        std::cout << "]\n";
        return; }
    size_t count = 0;
    bool first = true;
    if (begin < end) {
        for (const int* it = begin; it != end; ++it) {
            if (!first) std::cout << ", ";
            std::cout << *it;
            ++count;
            first = false;
            bool is_last = (it + 1 == end);
            if (line_limit > 0 && count == line_limit && !is_last) {
                std::cout << ", ...\n ";
                count = 0;
                first = true; }
        }} else { 
        for (const int* it = begin; it != end; --it) {
            if (!first) std::cout << ", ";
            std::cout << *it;
            ++count;
            first = false;
            bool is_last = (it - 1 == end - 1);
            if (line_limit > 0 && count == line_limit && !is_last) {
                std::cout << ", ...\n ";
                count = 0;
                first = true;}}
    }
    std::cout << "]\n";
}
