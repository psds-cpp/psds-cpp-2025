#include <stdexcept>


void SwapPtr(int*& ptr1, int*& ptr2) {
    int* ptr0 = ptr1;
    ptr1 = ptr2;
    ptr2 = ptr0;
}
void SwapPtr(const int*& ptr1, const int*& ptr2) {
    const int* ptr0 = ptr1;
    ptr1 = ptr2;
    ptr2 = ptr0;
}
void SwapPtr(int**& ptr1, int**& ptr2) {
    int** ptr0 = ptr1;
    ptr1 = ptr2;
    ptr2 = ptr0;
}

