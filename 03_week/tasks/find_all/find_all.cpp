#include <stdexcept>
#include <vector>

std::vector<size_t> FindAll(const std::vector<int>& vector, bool (*func)(int)) {
    if (!func) return {};

    size_t count = 0;
    for (int value : vector) {
        if (func(value)) ++count;
    }
    
    std::vector<size_t> positions;
    positions.reserve(count);
    
    for (size_t i = 0; i < vector.size(); ++i) {
        if (func(vector[i])) positions.push_back(i);
    }
    
    return positions;
}