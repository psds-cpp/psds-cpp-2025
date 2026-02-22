const char* FindLongestSubsequence(const char* begin, const char* end, size_t &count) {
    if (begin == nullptr || end == nullptr || begin >= end){
        count = 0;
        return nullptr;
    }

    const char* startOfSubsequence = begin;
    const char* left = begin;
    const char* right = ++begin;
    int max_length = 1;
    int length = 1;

    while (right != end)
    {
        if (*left == *right){
            ++right;
            ++length;
        } else { 
            if (length > max_length){
                startOfSubsequence = left;
                max_length = length;
            }
            
            length = 0;
            left = right;
        }
    }

    if (length > max_length){
        startOfSubsequence = left;
        max_length = length;
    }

    count = max_length;
    return startOfSubsequence;
}

char* FindLongestSubsequence(char* begin, char* end, size_t &count) {
    // Вызываем константную версию
    const char* result = FindLongestSubsequence(
        const_cast<const char*>(begin), 
        const_cast<const char*>(end), 
        count
    );
    // Снимаем константность
    return const_cast<char*>(result);
}