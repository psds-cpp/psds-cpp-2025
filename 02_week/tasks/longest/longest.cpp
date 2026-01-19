#include <stdexcept>

// Общая подфункция через const char*
const char* FindLongestSubsequenceImpl(const char* p1, const char* p2, size_t& count) {
    if (p1 == nullptr || p2 == nullptr) {
        count = 0;
        return nullptr;
    }
    
    if (p1 > p2) {
        count = 0;
        return nullptr;
    }
    
    if (p1 == p2) {
        count = 0;
        return nullptr;
    }
    
    const char* pp1 = p1;
    const char* max_p = nullptr;
    size_t c = 1;
    size_t max_c = 0;
    
    while (pp1 != p2) {
        if (pp1 + 1 != p2 && *pp1 == *(pp1 + 1)) {
            ++c;
        } else {
            if (c > max_c) {
                max_c = c;
                max_p = pp1 - c + 1; 
            }
            c = 1;
        }
        ++pp1;
    }
    
    if (c > max_c) {
        max_c = c;
        max_p = pp1 - c; 
    }
    
    count = max_c;
    return max_p;
}

// Перегрузка функций для сhar и const char
const char* FindLongestSubsequence(const char* p1, const char* p2, size_t& count) {
    return FindLongestSubsequenceImpl(p1, p2, count);
}

char* FindLongestSubsequence(char* p1, char* p2, size_t& count) {
    return const_cast<char*>(FindLongestSubsequenceImpl(p1, p2, count));
}
