#include <stdexcept>

const int* FindLastElement(const int* begin, const int* end, bool predicate(int x))
{
    if (predicate && begin && end)
    {
        size_t size = end - begin;
        for (long i = size-1; i>=0; --i)
        {
            if (predicate(begin[i]))
            {
                return (begin + i);
            }
        }
    }
    return end;
}