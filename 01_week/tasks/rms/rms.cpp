#include <cstddef>
#include <stdexcept>
#include <cmath>


double CalculateRMS(double values[], size_t size) {
    if(values == nullptr || size == 0){
        return 0.0;
    }

    double res {0.0};
    for(size_t i = 0; i < size; ++i){
        res += values[i] * values[i];
    }
    return std::sqrt(res / size);
}