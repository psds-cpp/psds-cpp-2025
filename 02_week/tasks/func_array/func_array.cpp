#include <cstddef>
#include <stdexcept>


double ApplyOperations(double a, double b, double (*funcs[])(double a, double b), size_t size) {
    double res = 0.0;
    for (size_t i = 0; i < size; ++i)
        if (funcs[i])
            res += funcs[i](a, b);
    return res;
}