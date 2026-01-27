#include <stdexcept>
#include <iostream>
#include <cmath>

void PrintArray(std::nullptr_t, std::nullptr_t)
{
    std::cout<<"[]\n";
}




template<typename T>
void PrintArray(T* begin, T* end, size_t limiter = 0)
{
    if (begin && end && begin != end)
    {
        std::cout << '[';
        
        size_t len = abs(begin-end);
        if (begin < end)
        {
            for (size_t i = 0; i < len; ++i)
            {
                if (limiter && i != 0 && !(i % limiter))
                    std::cout << "...\n" << ' ';
                
                i!=(len-1)? ( std::cout << begin[i] << ", "): ( std::cout << begin[i] << "]\n");
                            
            }
            
        }
        else
        {
            for (size_t i = 0; i < len; ++i)
            {
                if (limiter && i != 0 && !(i % limiter))
                    std::cout << "...\n" << ' ';
                T *current = begin - i;
                current == end + 1 ? (std::cout << *current) : (std::cout << *current << ", ");
            }
            std::cout<<"]\n";
        }
    }
    else
    {
        std::cout<<"[]\n";
    }
}


