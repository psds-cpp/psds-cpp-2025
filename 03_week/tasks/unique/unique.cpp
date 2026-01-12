#include <vector>

std::vector<int> Unique(const std::vector<int>& values) {
    std::vector<int> result;
    if (values.empty()) {
        return result;}
    result.reserve(values.size());
    result.push_back(values[0]);
    for (size_t i = 1; i < values.size(); ++i) {
        if (values[i] != values[i - 1]) {
            result.push_back(values[i]); }
    }
    result.shrink_to_fit();
    return result;
}
