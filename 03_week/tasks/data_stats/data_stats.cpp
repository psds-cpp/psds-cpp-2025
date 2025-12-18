#include <cmath>
#include <vector>

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
    
    long long sum = 0;
    for (int value : data) {
        sum += value;
    }
    result.avg = static_cast<double>(sum) / n;
    
    if (n == 1) {
        return result;
    }
    
    double sum_sq_diff = 0.0;
    for (int value : data) {
        double diff = value - result.avg;
        sum_sq_diff += diff * diff;
    }
    
    double variance = sum_sq_diff / n;
    result.sd = std::sqrt(variance);
    
    return result;
}
