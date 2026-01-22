#include <stdexcept>


const char* FindLongestSubsequence(const char* begin, const char* end, size_t& count) {
    const char* start_of_longest_seq = nullptr;
    count = 0;
    size_t this_seq_count = 0;

    if ((begin == nullptr) || (end==nullptr) || (begin > end)) {
        return start_of_longest_seq;
    }

    const char* next_el = nullptr;
    while(begin != end){
        this_seq_count = 1;
        if (begin < end - 1){
            next_el = begin + 1;
            for (; next_el != end; ++next_el){
                if (*next_el != *begin) break;
                ++this_seq_count;
            }
        }

        if (this_seq_count > count){
            count = this_seq_count;
            start_of_longest_seq = begin;
        }
        begin += this_seq_count;
    }

    return start_of_longest_seq;
}

char* FindLongestSubsequence(char* begin, char* end, size_t& count){
    const char* const_result = FindLongestSubsequence(const_cast<const char*>(begin), const_cast<const char*>(end), count);
    return const_cast<char*>(const_result);
}