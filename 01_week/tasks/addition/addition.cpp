#include <cstdint>
#include <stdexcept>


int64_t Addition(int a, int b) {
    int64_t res = static_cast<int64_t>(a) + b;  //явно преобразуем одно из слагаемых в int64_t
    return res;
}