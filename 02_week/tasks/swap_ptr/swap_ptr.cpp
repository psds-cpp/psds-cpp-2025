#include <stdexcept>

template<typename T>
void SwapPtr(T*& p1, T*& p2) {
    T* temp_p = p1;
    p1 = p2;
    p2 = temp_p;
}