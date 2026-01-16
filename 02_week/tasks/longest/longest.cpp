#include <cstddef>


char* FindLongestSubsequence(const char* begin, const char* end, size_t& count) {
    char* res{nullptr};
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

        res = count < curLen ? const_cast<char*>(curBegin) : res;
        count = count < curLen ? curLen : count;
        curLen = 1;
    }

    return res;
}
