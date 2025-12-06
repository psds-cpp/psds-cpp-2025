#include <cstddef>


char* FindLongestSubsequence(const char* begin, const char* end, size_t& count) {
    char* res{nullptr};
    count = 0;

    if(begin == nullptr || end == nullptr) return nullptr;

    size_t curLen{1};
    char* curBegin{const_cast<char*>(begin)};
    for(char* curent = const_cast<char*>(begin); curent < end; ++curent){
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
