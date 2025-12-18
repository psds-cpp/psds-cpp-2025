#include <stdexcept>
#include <vector>


std::vector<size_t> FindAll(const std::vector<int>& vec, bool (*pred_func) (int)) {
    std::vector<size_t> result;
    if (!pred_func || vec.empty())
        return result;
    result.reserve(vec.size());
    for (size_t i = 0; i < vec.size(); ++i){
        if (pred_func(vec[i])){
            result.push_back(i);
        }
    }
    result.shrink_to_fit();
    return result;
}
