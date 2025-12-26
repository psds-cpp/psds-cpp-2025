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
        result.avg += static_cast<double>(x);
    result.avg /= container.size();
    
    for (int x : container)
        result.sd += pow(x - result.avg, 2);
    result.sd /= container.size();
    result.sd = sqrt(result.sd);
    
    return result;
}
