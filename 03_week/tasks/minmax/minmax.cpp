#include <stdexcept>
#include <utility>

std::pair <std::vector<int>::const_iterator, std::vector<int>::const_iterator> MinMax(const std::vector <int>& vec) {
    if (vec.empty()) {
        return {vec.end(), vec.end()};
    }
    int min = vec[0];
    int max = vec[0];
    auto min_it = vec.begin();
    auto max_it = vec.begin();
    for (auto it = vec.begin(); it!= vec.end(); ++it){
        if (*it < min){
            min = *it;
            min_it = it;
        }
        if (*it >= max){
            max = *it;
            max_it = it;
        }
    }
    return {min_it, max_it};
}
