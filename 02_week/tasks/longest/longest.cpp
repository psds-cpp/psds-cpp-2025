#include <stdexcept>

template<typename CharType>
CharType* FindLongestSubsequenceImpl(CharType* begin, CharType* end, size_t& count) {
    if (begin == nullptr || end == nullptr || begin > end) {
        count = 0;
        return nullptr;
    }
    
    if (begin == end) {
        count = 0;
        return nullptr;
    }
    
    CharType* longest_start = begin;
    size_t longest_length = 1;
    CharType* current_start = begin;
    size_t current_length = 1;
    
    for (CharType* ptr = begin; ptr < end - 1; ++ptr) {
        if (*ptr == *(ptr + 1)) {
            current_length++;
        } else {
            if (current_length > longest_length) {
                longest_length = current_length;
                longest_start = current_start;
            }
            current_start = ptr + 1;
            current_length = 1;
        }
    }
    
    if (current_length > longest_length) {
        longest_length = current_length;
        longest_start = current_start;
    }
    
    count = longest_length;
    return longest_start;
}

const char* FindLongestSubsequence(const char* begin, const char* end, size_t& count) {
    return FindLongestSubsequenceImpl(begin, end, count);
}

char* FindLongestSubsequence(char* begin, char* end, size_t& count) {
    return FindLongestSubsequenceImpl(begin, end, count);
}
