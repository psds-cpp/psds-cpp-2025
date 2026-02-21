#include <vector>


auto MinMax(const std::vector<int>& vec) {
    auto min_it { vec.cend() };
    auto max_it { vec.cend() };

    if (vec.empty()) {
        return std::make_pair(min_it, max_it);
    }

    min_it = vec.cbegin();
    max_it = vec.cbegin();

    for (auto it = vec.cbegin(); it != vec.cend(); ++it) {
        if (*it < *min_it) {
            min_it = it;
        }
        if (*it >= *max_it) {
            max_it = it;
        }
    }

    return std::make_pair(min_it, max_it);
}