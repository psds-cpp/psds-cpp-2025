#include <stdexcept>
#include <vector>

std::vector<int> Unique(const std::vector<int>& vec) {
    if (vec.empty()) {
        return std::vector<int>();
    }

    size_t unique_count = 1;
    for (size_t i = 1; i < vec.size(); ++i) {
        if (vec[i] != vec[i - 1]) {
            ++unique_count;
        }
    }

    std::vector<int> result;
    result.reserve(unique_count);
    result.push_back(vec[0]);

    for (size_t i = 1; i < vec.size(); ++i) {
        if (vec[i] != vec[i - 1]) {
            result.push_back(vec[i]);
        }
    }

    return result;
}