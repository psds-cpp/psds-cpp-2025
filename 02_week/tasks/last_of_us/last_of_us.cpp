#include <stdexcept>


const int* FindLastElement(const int* begin, const int* end, bool (*predicate)(int)) {
    if (begin == nullptr || begin == nullptr || begin > end || begin == end) {
        return end;
    }
    for (const int* ptr = end - 1; ptr >= begin; --ptr) {
        if (predicate(*ptr)) {
            return ptr;
        }
    }
    return end;
}