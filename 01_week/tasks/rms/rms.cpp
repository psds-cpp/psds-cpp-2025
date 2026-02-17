#include <stdexcept>
#include <cmath>

double CalculateRMS(double values[], size_t size) {
    if (size == 0 || values == nullptr) {
        return 0.0;
    }
    
    double sum_of_squares = 0.0;
    for (size_t i = 0; i < size; ++i) {
        sum_of_squares += values[i] * values[i];
    }
    
    double mean_of_squares = sum_of_squares / size;
    double rms = std::sqrt(mean_of_squares);
    
    return rms;
}
