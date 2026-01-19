#include <stdexcept>
#include <vector>
#include <cmath>


struct DataStats {
    double avg = 0.0;
    double sd = 0.0;
};

DataStats CalculateDataStats(const std::vector<int>& vec) {
    if (vec.empty()) {
        return DataStats{0.0, 0.0};
    }

    long double sum = 0.0;
    long double sum_sq = 0.0;
    
    for (int x : vec) {
        long double ld_x = static_cast<long double>(x);
        sum += ld_x;
        sum_sq += ld_x * ld_x;
    }
    
    long double avg = sum / vec.size();
    long double variance = (sum_sq / vec.size()) - (avg * avg);
    
    // Защита от ошибок округления
    if (variance < 0.0) {
        variance = 0.0;
    }
    
    double sd = static_cast<double>(std::sqrt(variance));
    
    return DataStats{static_cast<double>(avg), sd};
}
