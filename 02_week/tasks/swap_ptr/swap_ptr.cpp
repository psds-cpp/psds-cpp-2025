#include <stdexcept>
#include <iostream>
// Есть три вида Template parameters:
// 1. constant template parameter 
// 2. type template parameter (нам нужен этот)
// 3. template template parameter

template <typename T> // параметр-тип
void SwapPtr(T*& a, T*& b) {
    T* ptr = a; // сохраняем адрес из a
    a = b; // кладём в a адрес из b
    b = ptr; // в b кладём старый адрес a
}


// это для визуальной проверки
/* int main() {
    int x = 1;
    int y = 2;

    int* a = &x;
    int* b = &y;

    std::cout << "До SwapPtr\n";
    std::cout << "Адрес a = " << a << ", *a = " << *a << "\n";
    std::cout << "Адрес b = " << b << ", *b = " << *b << "\n";

    SwapPtr(a, b);

    std::cout << "После SwapPtr\n";
    std::cout << "Адрес a = " << a << ", *a = " << *a << "\n";
    std::cout << "Адрес b = " << b << ", *b = " << *b << "\n";

    return 0;
} */
    