#include <vector>

using Predicate = bool (*)(int);

std::vector<size_t> FindAll(const std::vector<int>& vec, Predicate predicate) {
    std::vector<size_t> result;
    
    if (!predicate) {
        return result;
    }
    
    for (size_t i = 0; i < vec.size(); ++i) {
        if (predicate(vec[i])) {
            result.push_back(i);
        }
    }
    
    result.shrink_to_fit();
    
    return result;
}