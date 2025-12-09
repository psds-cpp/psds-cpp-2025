#include <stdexcept>

double ApplyOperations(double a, double b, double (**operations)(double, double), size_t n) {
    double total = 0.0;
    
    if (operations == nullptr || n == 0) {
        return total;}
    
    for (size_t i = 0; i < n; ++i) {
        if (operations[i] != nullptr) {
            total += operations[i](a, b);}
    }
    
    return total;
}