#include <cstddef>
#include <stdexcept>
#include <cmath>


double CalculateRMS(double values[], size_t size) {
    if (size == 0 || values == nullptr) {
        return 0.0;
    }

    double sumofSquares = 0.0;
    for (size_t i = 0; i < size; ++i) {
        sumofSquares += values[i] * values[i];
    }

    double meanofSquares = sumofSquares / static_cast<double>(size);
    return std::sqrt(meanofSquares);
}