#include <stdexcept>
#include <iterator>

const int* FindLastElement(const int* begin, const int* end, bool (*predicate) (const int)) {
    if ((end - begin) <= 0 || end == nullptr || begin == nullptr){
        return end;
    }
    const int* last = end;
    for (; begin < end; ++begin){
        if (predicate(*begin)) {
            last = begin;
        }
    }
    return last;
}
