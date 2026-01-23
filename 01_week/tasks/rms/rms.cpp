#include <cstddef>
#include <stdexcept>
#include <cmath>



double CalculateRMS(double values[], size_t size) {
    if (values == nullptr || size == 0) {
        return 0.0;
    }
    
    double sum = 0.0;
    for (size_t i = 0; i < size; ++i) {
        sum += values[i] * values[i];
    }
    
    double sqavg = sum / size;
    return std::sqrt(sqavg);
}