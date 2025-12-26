int* FindLastElement(const int* begin, const int* end, bool (*predicate)(int)) {
    if (!begin || !end || !predicate || begin > end)
        return const_cast<int*>(end);

    int* last = const_cast<int*>(end);

    for (; begin < end; ++begin) {
        if (predicate(*begin)) {
            last = const_cast<int*>(begin);
        }
    }

    return last;
}