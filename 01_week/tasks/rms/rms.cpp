#include <cstddef>
#include <stdexcept>
#include <cmath>


double CalculateRMS(double values[], size_t size) {
    if (size == 0 || values == nullptr){
        return 0.0;
    }
    double rms = 0;
    for (size_t i = 0; i < size; ++i){
        rms += values[i] * values[i];
    }
    return sqrt(rms/size);
}