
void SwapPtr(int*& a, int*& b) {
    int* tmp = a;
    a = b;
    b = tmp;
}

void SwapPtr(const int*& a, const int*& b) {
    const int* temp = a;
    a = b;
    b = temp;
}

void SwapPtr(int**& a, int**& b) {
    int** temp = a;
    a = b;
    b = temp;
}