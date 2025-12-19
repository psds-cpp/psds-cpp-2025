#include <stdexcept>
#include <vector>

std::vector<int> Unique(const std::vector<int>& v) {
    if (v.empty()) {
        return {};
    }
    size_t uniq = 1;
    for (size_t i = 1; i < v.size(); ++i) {
        if (v[i] != v[i - 1]) {
            ++uniq;
        }
    }
    std::vector<int> res(uniq);
    res[0] = v[0];

    size_t index = 1;
    for (size_t i = 1; i < v.size(); ++i) {
        if (v[i] != v[i - 1]) {
            res[index] = v[i];
            ++index;
        }
    }

    return res;
}
