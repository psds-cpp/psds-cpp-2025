#include <vector>

// std::vector<size_t> FindAll(const std::vector<int>& container, bool (*predicate)(int)) {
//     std::vector<size_t> result;
    
//     if (!predicate) {
//         return result;
//     }
    
//     size_t count = 0;
//     for (size_t i = 0; i < container.size(); ++i) {
//         if (predicate(container[i])) {
//             ++count;
//         }
//     }
    
//     result.reserve(count);
    
//     for (size_t i = 0; i < container.size(); ++i) {
//         if (predicate(container[i])) {
//             result.push_back(i);
//         }
//     }
    
//     return result;
// }

std::vector<size_t> FindAll(const std::vector<int>& container, bool(*pred)(int)) {
    std::vector<size_t> result;
    if (!pred) {
        return result;
    }

    
    for (size_t i = 0; i < container.size(); ++i) {
        if (pred(container[i])) {
            result.push_back(i);
        }
    }

    result.shrink_to_fit();
    return result;
}