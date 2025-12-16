#include <vector>
#include <stddef.h>


std::vector<int> Unique(const std::vector<int>& arr) {
    std::vector<int> unique{};
    unique.reserve(arr.size());

    for (size_t i = 0; i < arr.size(); ++i) {
        if (unique.empty() || unique[unique.size() - 1] != arr[i]) {
            unique.push_back(arr[i]);
        }
    }

    unique.shrink_to_fit();
    return unique;
}
