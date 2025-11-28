#include <cstdef>
#include <stdexcept>
#include <cmath>

double CalculateRMS(double values[], size_t size) {
    // Обработка пустого массива
    if (size == 0) {
        return 0.0;
    }
    
    // Сумма квадратов элементов
    double sum_of_squares = 0.0;
    
    for (size_t i = 0; i < size; ++i) {
        sum_of_squares += values[i] * values[i];
    }
    
    // Среднее значение квадратов
    double mean_of_squares = sum_of_squares / size;
    
    // Корень из среднего значения квадратов
    return std::sqrt(mean_of_squares);
}