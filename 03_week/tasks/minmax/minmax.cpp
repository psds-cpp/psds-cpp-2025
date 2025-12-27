#include <stdexcept>
#include <vector>
#include <utility>

std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator> MinMax(const std::vector<int>& vec) {
    if (vec.empty()) {
        return {vec.end(), vec.end()};
    }

    if (vec.size() == 1) {
        return {vec.begin(), vec.begin()};
    }

    auto min_it = vec.begin();
    auto max_it = vec.begin();
    auto it = vec.begin() + 1;
    if (vec.size() % 2 == 0) {
        if (*it < *min_it) {
            min_it = it;
        } else if (*it >= *max_it) {
            max_it = it;
        }
        ++it;
    }

    while ((it + 1) < vec.end()) {
        auto it1 = it;
        auto it2 = it + 1;

        if (*it1 <= *it2) {
            if (*it1 < *min_it) {
                min_it = it1;
            }
            if (*it2 >= *max_it) {
                max_it = it2;
            }
        } else {
            if (*it2 < *min_it) {
                min_it = it2;
            }
            if (*it1 >= *max_it) {
                max_it = it1;
            }
        }

        it += 2;
    }

    if (it != vec.end()) {
        if (*it < *min_it) {
            min_it = it;
        } else if (*it >= *max_it) {
            max_it = it;
        }
    }

    return {min_it, max_it};
}