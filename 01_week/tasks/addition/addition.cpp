#include <cstdint>
#include <stdexcept>


int64_t Addition(int a, int b) {
int64_t res = static_cast<int64_t>(a);    // Присвоение и приведение типов.
res = res + static_cast<int64_t>(b);      // Вычисление суммы и приведение типов.
    return res;
}
