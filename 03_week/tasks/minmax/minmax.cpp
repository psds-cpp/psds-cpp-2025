#include <climits>
#include <limits>
#include <utility>
#include <vector>

using ItMin = std::vector<int>::const_iterator;
using ItMax = std::vector<int>::const_iterator;

std::pair<ItMin, ItMax> MinMax(const std::vector<int>& v) {
    if (v.empty()) {
        return {v.end(), v.end()};
    }

    auto minIt = v.begin();
    auto maxIt = v.end();    
    int min = std::numeric_limits<int>::max();
    int max = std::numeric_limits<int>::min();

    for (auto it = v.begin(); it != v.end(); ++it) {
        if (*it < min) {
            min = *it;
            minIt = it;
        }

        if (*it >= max) {
            max = *it;
            maxIt = it;
        }
    }
    
    return {minIt, maxIt};
}
