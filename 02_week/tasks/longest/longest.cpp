#include <stdexcept>

char *FindLongestSubsequence(char *begin, char *end, size_t &count)
{
    count = 0;
    if (begin && end)
    {

        char *subsequence = nullptr;
        for (long i = 0; i < end - begin; ++i)
        {
            char *newsequence = begin + i;
            size_t t = 1;
            while (*newsequence == *(newsequence + t) && newsequence + t < end)
            {
                ++i;
                ++t;
            }
            if (t > count)
            {
                count = t;
                subsequence = newsequence;
            }
        }
        return subsequence;
    }
    return nullptr;
}

const char *FindLongestSubsequence(const char *begin, const char *end, size_t &count)
{
    count = 0;
    size_t pos = 0;
    if (begin && end)
    {

        for (long i = 0; i < end - begin; ++i)
        {
            size_t t = 1;
            const char *newsubsequence = begin + i;
            while (*newsubsequence == *(newsubsequence + t) && i < end - begin - 1)
            {
                ++i;
                ++t;
            }
            if (t > count)
            {
                count = t;
                pos = i - t + 1;
            }
        }
        return begin + pos;
    }
    return nullptr;
}
