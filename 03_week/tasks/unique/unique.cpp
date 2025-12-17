#include <vector>

auto Unique(const std::vector<int>& vec) {
    std::vector<int> res;

    if (vec.empty()) {
        return res;
    }

    size_t count = 1;

    for (size_t i = 0; i < vec.size() - 1; ++i) {
        
        if (vec[i] != vec[i + 1]) {
            ++count;
        }
    }

    res.reserve(count);
    res.push_back(vec[0]);

    for (size_t i = 0; i < vec.size() - 1; ++i) {
        
        if (vec[i] != vec[i + 1]) {
            res.push_back(vec[i + 1]);
        }
    }

    return res;
}