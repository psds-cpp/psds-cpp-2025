#include <cmath>


double CalculateRMS(double values[], size_t size) {
    if (size == 0 || values == nullptr) return .0;

    double result = 0;
    for (size_t i = 0; i < size; ++i) {
        result += values[i]*values[i];
    }

    // size неявно преобразуется к double
    return std::sqrt(result / size);
}