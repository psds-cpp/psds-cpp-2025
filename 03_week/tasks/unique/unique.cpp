#include <stdexcept>
#include <vector>

std::vector<int> Unique(const std::vector<int>& vec) {
    if (vec.size() == 0)
        return {};

    size_t len = vec.size();
    size_t cnt = 1;
    for (size_t i = 1; i < len; ++i)
        if (vec[i] != vec[i - 1])
            ++cnt;

    std::vector<int> result;
    result.reserve(cnt);

    result.push_back(vec[0]);
    for (size_t i = 1; i < len; ++i)
        if (vec[i] != vec[i - 1])
            result.push_back(vec[i]);

    return result;
}
