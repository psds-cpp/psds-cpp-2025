#include <stdexcept>
#include <vector>

std::vector<int> Unique(const std::vector<int>& vec) {
    std::vector<int> result;
    
    if (vec.empty()) {
        return result;  
    }
    
    result.reserve(vec.size());
    
    
    result.push_back(vec[0]);
    
    for (size_t i = 1; i < vec.size(); ++i) {
        if (vec[i] != result.back()) {
            result.push_back(vec[i]);
        }
    }
    
    result.shrink_to_fit();
    
    return result;
}