#include <stdexcept>


 const int* FindLastElement(const int* begin, const int* end, bool (*predicate)(int)) {
    if (begin > end || begin == end || end == nullptr || begin == nullptr) {
        return end;
    }
    const int* p_pred = end;
    
    for (size_t i = 1; (end-i) != (begin-1); ++i) {
        if (predicate(*(end-i))) {
            p_pred = end-i;
            return p_pred;
        }
    }
    return p_pred;
}