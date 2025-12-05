const int* FindLastElement(const int* begin, const int* end, bool (*predicate)(int)) {
    if (!begin || !end || !predicate) {
        return end;
    }

    if (begin > end) {
        return end;
    }
    
    for (const int *p = end - 1; p != begin - 1; p--) {
        if (predicate(*p)) {
            return p;
        }
    }

    return end;
}