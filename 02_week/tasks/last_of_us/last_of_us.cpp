#include <stdexcept>


const int* FindLastElement(const int* begin, const int* end, bool (*predicate)(int a)) {
    if (!(begin && end && predicate && begin < end))
        return end;
    const int* first = begin;
    const int* last = end-1;
    for (; last >= first; --last)
        if (predicate(*last))
            return last;
    return end;
}