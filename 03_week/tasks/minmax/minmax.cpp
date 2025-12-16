#include <vector>
#include <stddef.h>


struct MinMaxResult {
    std::vector<int>::const_iterator min_it{};
    std::vector<int>::const_iterator max_it{};
};


MinMaxResult MinMax(const std::vector<int>& arr) {
    MinMaxResult result{arr.end(), arr.end()};

    if (arr.empty()) return result;

    result = {arr.begin(), arr.begin()};

    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i] >= *result.max_it) {
            result.max_it = arr.begin() + i;
        }
        else if (arr[i] < *result.min_it) {
            result.min_it = arr.begin() + i;
        }
    }

    return result;
}
