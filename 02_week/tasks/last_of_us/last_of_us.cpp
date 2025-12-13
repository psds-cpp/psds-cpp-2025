#include <stdexcept>

typedef bool (*Predicate)(int);

const int* FindLastElement(const int* begin, const int* end, Predicate predicate) {
    if (begin == nullptr || end == nullptr || begin > end || predicate == nullptr) {
        return end;
    }
    
    for (const int* current = end - 1; current >= begin; --current) {
        if (predicate(*current)) {
            return current;
        }
    }
    
    return end;
}
