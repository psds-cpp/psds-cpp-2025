#include <cstddef>

const int* FindLastElement(const int* begin, const int* end, bool (*predicate)(int)) {
    if (!begin || !end || !predicate || begin > end)
        return end;

    const int* last = end;

    for (; begin < end; ++begin) {
        if (predicate(*begin)) {
            last = begin;
        }
    }

    return last;
}

int* FindLastElement(int* begin, int* end, bool (*predicate)(int)) {
    return const_cast<int*>(
        FindLastElement(
            const_cast<const int*>(begin), 
            const_cast<const int*>(end), 
            predicate
        )
    );
}

inline int* FindLastElement(std::nullptr_t, std::nullptr_t, bool (*)(int)) {
    return nullptr;
}