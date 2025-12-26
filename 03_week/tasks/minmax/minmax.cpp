#include <stdexcept>
#include <vector>


std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator> MinMax(const std::vector<int>& vector) {
    auto min_iter = vector.begin();
    auto max_iter = vector.begin();

    if (vector.empty()) return {vector.end(), vector.end()};

    for (auto iterator = vector.begin(); iterator != vector.end(); ++iterator){
        if (*iterator < *min_iter) min_iter = iterator;
        if (*iterator >= *max_iter) max_iter = iterator;
    }

    return {min_iter, max_iter};
}
