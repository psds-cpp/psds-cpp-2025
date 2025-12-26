#include <cstddef>


double ApplyOperations(const double a, const double b, double (*func_arr[])(double, double), const size_t size) {
    if (size == 0) return 0;

    double result = 0;

    for (size_t i = 0; i < size; ++i) {
        if (func_arr[i])
            result += func_arr[i](a, b);
    }

    return result;
}