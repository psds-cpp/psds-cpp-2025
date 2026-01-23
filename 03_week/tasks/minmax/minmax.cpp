#include <stdexcept>
#include <vector>
#include <utility>

std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator> 
MinMax(const std::vector<int>& vec) {
    if (vec.empty()) {
        return {vec.end(), vec.end()};
    }
    
    auto min_it = vec.begin();
    auto max_it = vec.begin();
    
    for (auto it = vec.begin() + 1; it != vec.end(); ++it) {
        if (*it < *min_it) {
            
            min_it = it;
        } else if (*it > *max_it) {
            
            max_it = it;
        } else if (*it == *max_it) {
            
            max_it = it;
        }
    }
    
    return {min_it, max_it};
}

std::pair<std::vector<int>::iterator, std::vector<int>::iterator> 
MinMax(std::vector<int>& vec) {
    if (vec.empty()) {
        return {vec.end(), vec.end()};
    }
    
    auto min_it = vec.begin();
    auto max_it = vec.begin();
    
    for (auto it = vec.begin() + 1; it != vec.end(); ++it) {
        if (*it < *min_it) {
            min_it = it;
        } else if (*it > *max_it) {
            max_it = it;
        } else if (*it == *max_it) {
            max_it = it;
        }
    }
    
    return {min_it, max_it};
}