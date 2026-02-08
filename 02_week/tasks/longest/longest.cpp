#include <stdexcept>

const char* FindLongestSubsequence(const char* begin, const char* end, size_t& count) {
    if (!begin || !end || begin >= end) {
        count = 0;
        return nullptr;
    }

    size_t maxCount = 0;
    const char* startPtr = nullptr;
    const char* current = begin;

    while (current < end) {
        const char* run = current;
        while (run < end && *run == *current) {
            run++;
        }

        size_t curLen = run - current;
        if (curLen > maxCount) {
            maxCount = curLen;
            startPtr = current;
        }
        current = run;
    }

    count = maxCount;
    return startPtr;
}

char* FindLongestSubsequence(char* begin, char* end, size_t& count) {
    return const_cast<char*>(
        FindLongestSubsequence(static_cast<const char*>(begin), 
                               static_cast<const char*>(end), 
                               count)
    );
}