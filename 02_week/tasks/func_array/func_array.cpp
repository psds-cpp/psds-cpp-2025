#include <stdexcept>


double ApplyOperations(double a, double b, double (**funks)(double, double), size_t size) {
    if (funks == nullptr || size == 0) {
        return 0.0;
    }

    double Sum = 0.0;

    for (size_t i = 0; i < size; ++i) {
        if (funks[i] != nullptr) {
            Sum += funks[i](a, b);
        }
    }

    return Sum;
}
