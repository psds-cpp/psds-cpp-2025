#include <stdexcept>
#include <vector>

struct DataStats {
    double avg = 0.0;
    double sd = 0.0;
};

DataStats CalculateDataStats(const std::vector<int>& data) {
    DataStats p;
    if (data.empty()) return p;
    double sum_of_x = 0.0;
    double sum_of_squares_x = 0.0;
    size_t N = data.size();
    for (size_t i = 0; i < N; ++i){
        sum_of_x += data[i];
        sum_of_squares_x += static_cast<double>(data[i])*data[i];
    }
    p.avg = sum_of_x/N;
    double variance = (sum_of_squares_x/N) - (sum_of_x/N)*(sum_of_x/N);
    p.sd = sqrt(variance);
    return p;
}
