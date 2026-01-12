#include <vector>
#include <stdexcept>

std::vector<size_t> FindAll(const std::vector<int>& v, bool (*pred)(int)) {
    std::vector<size_t> result;
    if (!pred) {
        return result;}
    result.reserve(v.size());
    for (size_t i = 0; i < v.size(); ++i) {
        if (pred(v[i])) {
            result.push_back(i);}
    }
    result.shrink_to_fit();
    return result;
}
