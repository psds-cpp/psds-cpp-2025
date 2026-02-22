#include <cstddef>

using funcPtr = bool (*)(int);

const int* FindLastElement(const int* begin, const int* end, funcPtr predicate) {
    if (begin == nullptr || end == nullptr || predicate == nullptr){
        return end;
    }

    if (begin >= end){
        return end;
    }

    const int* last_element = end;

    while (begin < end)
    {
        --end;
        if (predicate(*end)){
            return end;
        }
    }
    
    return last_element;
}