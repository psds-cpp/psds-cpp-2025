typedef bool (*predicate_func_t)(int);

const int* FindLastElement(const int* begin, const int* end, predicate_func_t predicate) {
    if (!begin || !end || begin >= end) {
        return end;
    }
    
    const int* result = end;
    while (begin != end) {
        if (predicate(*begin)) {
            result = begin;
        }
        ++begin;
    }

    return result;
}
