#include <iostream>


void PrintArray(const int* begin, const int* end, size_t limit = 0) {
    if(begin == nullptr || end == nullptr){
        std::cout << "[]\n";
        return;
    }

    std::cout << "[";
    if(begin < end){
        size_t i = 1;
        for(const int* curent = begin; curent < end; ++curent){
            if(limit != 0 && i > limit){
                std::cout << "...\n " << *curent << (curent+1 == end ? "" : ", ");
                i = 1;
            }
            else{
                std::cout << *curent << (curent+1 == end ? "" : ", ");
            }
            ++i;
        }
    }
    else{
        size_t i = 1;
        for(const int* curent = begin; curent > end; --curent){
            if(limit != 0 && i > limit){
                std::cout << "...\n " << *curent << (curent-1 == end ? "" : ", ");
                i = 1;
            }
            else{
                std::cout << *curent << (curent-1 == end ? "" : ", ");
            }
            ++i;
        }
    }

    std::cout << "]\n";
}