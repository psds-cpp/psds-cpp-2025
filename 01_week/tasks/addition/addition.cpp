#include <cstdint>
#include <stdexcept>


int64_t Addition(int a, int b) {
    int64_t first = static_cast<int64_t>(a);
    int64_t second = static_cast<int64_t>(b);
    return first + second;
}