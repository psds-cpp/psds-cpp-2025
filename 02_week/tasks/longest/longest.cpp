#include <stdexcept>


char* FindLongestSubsequence(const char* begin, const char* end, size_t& count) {
    count = 0;
    if ((begin >= end) or (begin == nullptr) or (end == nullptr)){
        return nullptr;
    }
    char* long_begin = const_cast<char*>(begin);
    //char long_char = *begin;
    size_t len = 0;
    char* char0 = const_cast<char*>(begin);
    while (begin <= end){
        if(*char0 == *begin){
            len++;
        }
        else{
            if (len > count){
                count = len;
                //long_char = char0;
                long_begin = const_cast<char*>(char0);
            }
            char0 = const_cast<char*>(begin);
            len = 1;
        }

        begin++;
    }
    return long_begin;
}
