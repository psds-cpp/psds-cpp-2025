#include <stdexcept>
#include <vector>
#include <cmath>

struct DataStats {
    double avg = 0.0;
    double sd = 0.0;
};

DataStats CalculateDataStats(const std::vector<int>& data) {
    DataStats stats;
    
    if (data.empty()) {
        return stats;
    }
    
    double sum = 0.0;
    double sum_of_squares = 0.0;
    for (const int& value : data) {
        sum += value;
        sum_of_squares += static_cast<double>(value) * value;
    }

    stats.avg = sum / data.size();
    double variance = (sum_of_squares / data.size()) - (stats.avg * stats.avg);
	variance = variance >= 0.0 ? variance : 0.0;
    stats.sd = std::sqrt(variance);
    return stats;
}