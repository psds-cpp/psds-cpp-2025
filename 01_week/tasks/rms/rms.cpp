#include <stdexcept>
#include <cmath>
#include <cstddef>

double CalculateRMS(double values[], size_t size) {
    if (size == 0 || values == nullptr) {
        return 0.0;
    }
    
    // Вычисление суммы квадратов элементов
    double sum1 = 0.0;
    for (size_t i = 0; i < size; ++i) {
        sum1 += values[i] * values[i];
    }
    
    // Вычисление среднеквадратического значения
    double squares = sum1 / size;
    double rms = std::sqrt(squares);
    
    return rms;
}