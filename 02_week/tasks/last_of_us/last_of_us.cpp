#include <stdexcept>

const int* FindLastElement(const int* begin, const int* end, bool (*predicate)(int)) {
    
    if (begin == nullptr || end == nullptr || begin > end) {
        return end;
    }
    
    const int* last_found = end;
    
    // Проходим по массиву с конца к началу
    const int* current = end;
    while (current > begin) {
        --current; 
        if (predicate(*current)) {
            last_found = current;
            break;
        }
    }
    
    return last_found;
}
