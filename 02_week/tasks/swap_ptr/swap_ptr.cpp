#include <stdexcept>

void SwapPtr(int*& a, int*& b) {
    int* temp = a;
    a = b;
    b = temp;}
void SwapPtr(const int*& a, const int*& b) {//const int*
    const int* temp = a;
    a = b;
    b = temp;}
void SwapPtr(int**& a, int**& b) { //int
    int** temp = a;
    a = b;
    b = temp;}