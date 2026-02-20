#include <stdexcept>
#include <vector>
#include <cmath>

struct DataStats {
    double avg = 0.0;
    double sd = 0.0;
};

DataStats CalculateDataStats(const std::vector<int>& data) {
    DataStats result;
    size_t n = data.size();
    
    if (n == 0) {
          return result;
    }
    
    double sum = 0.0;
    for (int value : data) {
        sum += value;
    }
    
    // Вычисляем среднее значение
    result.avg = sum / n;
    
    if (n == 1) {
        
        result.sd = 0.0;
        return result;
    }
    
    double sum_squared_diff = 0.0;
    for (int value : data) {
        double diff = value - result.avg;
        sum_squared_diff += diff * diff;
    }
    
    result.sd = std::sqrt(sum_squared_diff / n);
    
    return result;
}