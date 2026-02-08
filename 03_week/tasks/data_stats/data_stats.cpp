#include <vector>
#include <cmath>


struct DataStats {
    double avg = 0.0;
    double sd = 0.0;
};

DataStats CalculateDataStats(const std::vector<int>& data) {
    DataStats res {0.0, 0.0};
    size_t size = 0;

    if(data.empty()) return res;

    for(int elem : data){
        res.avg += elem;
        res.sd += static_cast<double>(elem) * elem;
        ++size;
    }
    res.avg /= size;
    res.sd /= size;
    res.sd -= res.avg * res.avg;
    res.sd = std::sqrt(res.sd);

    return res;
}
