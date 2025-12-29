#include <vector>
#include <stddef.h>


std::vector<size_t> FindAll(const std::vector<int>& arr, bool (*bool_func)(int)) {
    std::vector<size_t> result{};

    if (!bool_func) return result;

    result.reserve(arr.size());

    for (size_t i = 0; i < arr.size(); ++i) {
        if (bool_func(arr[i])) {
            result.push_back(i);
        }
    }
    
    result.shrink_to_fit();
    return result;
}