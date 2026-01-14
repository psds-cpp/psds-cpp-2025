#include <stdexcept>


void SwapPtr(auto*& ptr1, auto*& ptr2) {
    auto* temp = ptr1;
    ptr1 = ptr2;
    ptr2 = temp;
}
