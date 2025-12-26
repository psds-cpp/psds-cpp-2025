#include <cstddef>


char* FindLongestSubsequence(const char* begin, const char* end, size_t& count) {
    if (!begin || !end || begin >= end) {
        count = 0;
        return nullptr;
    }

    int max_len = 1;
    int curr_len = 1;
    char* sub_begin = nullptr;
    char* result = const_cast<char*>(begin);

    for (; begin < end - 1; ++begin) {
        if (*(begin + 1) == *begin) {
            if (sub_begin == nullptr) {
                sub_begin = const_cast<char*>(begin);
            }
            ++curr_len;
            continue;
        }
        else if (curr_len > max_len) {
            max_len = curr_len;
            result = sub_begin;
            
        }

        curr_len = 1;
        sub_begin = nullptr;
    }

    if (curr_len > max_len) {
        max_len = curr_len;
        curr_len = 1;
        result = sub_begin;
    }

    count = max_len;

    return result;
}
