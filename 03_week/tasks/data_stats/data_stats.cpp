#include <stdexcept>
#include <bits/stdc++.h>

struct DataStats {
    double avg = 0.0;
    double sd = 0.0;
};

DataStats CalculateDataStats(std::vector<int> container) {
    DataStats result;
    
    if (container.size() == 0)
        return result;

    for (int x : container)
        result.avg += x;
    result.avg /= container.size();
    
    for (int x : container)
        result.sd += std::pow(x - result.avg, 2);
    
    result.sd = std::sqrt(result.sd / container.size());
    
    return result;
}
