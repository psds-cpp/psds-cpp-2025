
const int* FindLastElement(const int* begin, const int* end, bool (*predicate)(int)) {
    if(begin == nullptr || end == nullptr || begin > end) return end;

    for(const int* current = (end-1); current != begin-1; --current){
        if(predicate(*current)) return current;
    }
    return end;
}