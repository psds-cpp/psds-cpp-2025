#include <vector>
#include <utility>

auto MinMax(const std::vector<int>& vec) {
    if (vec.empty()) {
        return std::make_pair(vec.end(),vec.end());
    }

    auto min = vec.begin();
    auto max = vec.begin();
    
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        if (*it < *min) {
            min = it;
        }

        if (*it >= *max) {
            max = it;
        }
    }

    return std::make_pair(min, max);
}