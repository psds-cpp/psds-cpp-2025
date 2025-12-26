#include <cstddef>
#include <cmath>

double CalculateRMS(double values[], size_t size) {
    
    if (values == NULL) return static_cast<double>(0.0);
    
    if (size == 0) return static_cast<double>(0.0);

    double sum = 0.0;
    
    for (size_t i = 0; i < size; ++i) {
        sum += values[i] * values[i];
    }
    
    return sqrt(sum / size);
}
