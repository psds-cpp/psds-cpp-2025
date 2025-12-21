#include <vector>

std::vector<int> Unique(const std::vector<int>& vec) {
    std::vector<int> result {};

    if (vec.empty()) {
        return result;
    }

    result.reserve(vec.size());

    for (const auto& item : vec) {
        if (result.empty() || result.back() != item) {
            result.push_back(item);
        }
    }

    return (result.shrink_to_fit(), result);
}
