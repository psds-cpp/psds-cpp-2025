#include <cstddef>

const char* FindLongestSubsequence(const char* begin, const char* end, size_t& count) {
    const char* res{nullptr};
    count = 0;

    if(begin == nullptr || end == nullptr) return nullptr;

    size_t curLen{1};
    const char* curBegin{begin};
    for(const char* curent = begin; curent < end; ++curent){
        if(curent+1 != end && *curent == *(curent+1)){
            curBegin = curLen == 1 ? curent : curBegin;
            ++curLen;
            continue;
        }

        res = count < curLen ? curBegin : res;
        count = count < curLen ? curLen : count;
        curLen = 1;
    }

    return res;
}

char* FindLongestSubsequence(char* begin, char* end, size_t& count) {
    const char* const_res = FindLongestSubsequence(const_cast<const char*>(begin), const_cast<const char*>(end), count);
    return const_cast<char*>(const_res);
}