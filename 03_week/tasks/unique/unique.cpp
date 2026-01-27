#include <stdexcept>
#include <vector>

std::vector<int> Unique(const std::vector<int>& v) {
    std::vector<int> result;
    result.reserve(v.size());
    for (size_t i = 0; i < v.size(); ++i){
        bool is_in_result = false;
        for (size_t k = 0; k < result.size(); ++k){
            if (result[k] == v[i]){
                is_in_result = true;
            }
        }
        if (!is_in_result){
            result.push_back(v[i]);
        }

    }
    result.shrink_to_fit();
    return result;
}
