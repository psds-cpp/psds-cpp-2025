#include <cstdint>
#include <stdexcept>


int64_t Addition(int a, int b) {
    int64_t a_64 = static_cast<int64_t>(a);
    int64_t b_64 = static_cast<int64_t>(b);
    int64_t sum = a_64 + b_64;
    return sum;
}
