#include <stdexcept>
#include <vector>
#include <cmath>


std::vector<int> Range(int from, int to, int step = 1) {
    long long it = static_cast<long long>(std::ceil((to - from)/static_cast<double>(step)));
    if (step != 0 && to != from && it > 0){
        std::vector<int> result;
        result.reserve(it);
        for (size_t i = 0; i < static_cast<size_t>(it); ++i){
            result.push_back(from + step*i);
        }
        result.shrink_to_fit();
        return result;
    }
    else{
        std::vector<int> null;
        return null;
    }
}
