#include <stdexcept>




void SwapPtr(int*& a, int*& b)
{
    int* c = a;
    a = b;
    b = c;
}

void SwapPtr(const int*& a, const int*& b){
    const int* c = a;
    a = b;
    b = c;
}

void SwapPtr(int**& a, int**& b)
{
    int** c = a;
    a = b;
    b = c;
}


/* рабочий вариант через template для любого типа данных. на лекции не проходили, просто показать что я нашел и такую штуку
template<typename T>
void SwapPtr(T*& a, T*& b){
    T* c = a;
    a = b;
    b = c;
}
    */