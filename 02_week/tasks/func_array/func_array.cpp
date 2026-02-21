#include <stdexcept>


double ApplyOperations(double a, double b, double (**ops)(double, double), size_t size) {
    if (ops == nullptr || size == 0) {
        return 0.0;
    }
    
    double sum = 0.0;
    for (size_t i = 0; i < size; ++i) {
        if (ops[i] != nullptr) {
            sum += ops[i](a, b);
        }
    }
    
    return sum;
}