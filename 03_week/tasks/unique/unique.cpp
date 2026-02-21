#include <stdexcept>
#include <vector>

// std::vector<int> Unique(const std::vector<int>& sorted_vec) {
//     if (sorted_vec.empty()) {
//         return std::vector<int>();
//     }
    
//     std::vector<int> result;
//     result.reserve(sorted_vec.size());
    
//     result.push_back(sorted_vec[0]);
    
//     for (size_t i = 1; i < sorted_vec.size(); ++i) {
//         if (sorted_vec[i] != sorted_vec[i - 1]) {
//             result.push_back(sorted_vec[i]);
//         }
//     }
    
//     result.shrink_to_fit();
    
//     return result;
// }

std::vector<int> Unique(const std::vector<int>& vec) {
    if (vec.empty()) {
        return {};
    }

    std::vector<int> result;
    result.reserve(vec.size());
    result.push_back(vec[0]);

    for (size_t i = 1; i < vec.size(); ++i) {
        if (vec[i-1] != vec[i]) {
            result.push_back(vec[i]);
        }
    }
    result.shrink_to_fit();

    return result;
}