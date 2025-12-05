#include <cstddef>

char* FindLongestSubsequence(const char* begin, const char* end, size_t& count) {
    count = 0;
    
    if (!begin || !end) {
        return nullptr;
    }

    if (begin >= end) {
        return nullptr;
    }

    char prev_char = '\0';

    size_t prev_seq_len = 1;
    const char* prev_seq = begin;

    size_t max_seq_len = prev_seq_len;
    const char* max_seq = prev_seq;

    for (auto p = begin; p != end; ++p) {
        if (*p == prev_char) {
            ++prev_seq_len;
        }
        else {
            if (prev_seq_len > max_seq_len) {
                max_seq_len = prev_seq_len;
                max_seq = p - prev_seq_len;
            }

            prev_seq_len = 1;
            prev_seq = p;
        }

        prev_char = *p;
    }

    if (prev_seq_len > max_seq_len) {
        max_seq_len = prev_seq_len;
        max_seq = end - prev_seq_len;
    }

    count = max_seq_len;

    return const_cast<char*>(max_seq);
}