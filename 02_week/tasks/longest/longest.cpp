#include <stdexcept>


char* FindLongestSubsequence(char* begin, char* end, size_t& count) {
    if (!begin || !end || end - begin == 0) {
        count = 0;
        return nullptr;
    }

    size_t curLen = 0;
    char* startPtr = nullptr;
    char curChar = *begin;
    for (; begin <= end; ++begin) {
        if (curChar != *begin) {
            if (curLen > count) {
                count = curLen;
                startPtr = begin - curLen;
            }
            curLen = 1;
                curChar = *begin;
        }
        else
            ++curLen;
    }
    return startPtr;
}

const char* FindLongestSubsequence(const char* begin, const char* end, size_t& count) {
    return FindLongestSubsequence(const_cast<char*>(begin), const_cast<char*>(end), count);
}