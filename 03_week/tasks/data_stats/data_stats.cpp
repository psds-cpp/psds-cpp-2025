#include <vector>
#include <stddef.h>
#include <math.h>


struct DataStats {
    double avg = 0.0;
    double sd = 0.0;
};

DataStats CalculateDataStats(const std::vector<int>& arr) {
    DataStats data_stats{};

    if (arr.empty()) return data_stats;

    // Считаем обычную сумму и сумму квадратов вектора
    for (size_t i = 0; i < arr.size(); ++i) {
        data_stats.avg += arr[i];
        data_stats.sd += std::pow(arr[i], 2);
    }

    // По суммам считаем среднее и sd
    data_stats.avg /= arr.size();
    data_stats.sd = sqrt(data_stats.sd / arr.size() - std::pow(data_stats.avg, 2));

    return data_stats;
}
