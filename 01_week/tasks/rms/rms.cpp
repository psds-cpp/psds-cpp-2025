#include <stdexcept>
#include <cmath>


double CalculateRMS(double values[], size_t size) {
    if (!values || size == 0){
        return 0.0;
    }
    double sum_square = 0.0;
    for (size_t i = 0; i < size; ++i){
        sum_square += std::pow(values[i], 2);
    }
    double RMS = std::sqrt(sum_square/size);
    return RMS;
}
