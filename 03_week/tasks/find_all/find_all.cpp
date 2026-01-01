#include <vector>


std::vector<size_t> FindAll(const std::vector<int>& vec, bool (*predicate)(int)) {
    std::vector<size_t> indices {};
    
    if (vec.empty() || predicate == nullptr) {
        return indices;
    }

    indices.reserve(vec.size());
    
    for (size_t i = 0; i < vec.size(); ++i) {
        if (predicate(vec[i])) {
            indices.push_back(i);
        }
    }

    return (indices.shrink_to_fit(), indices);
}