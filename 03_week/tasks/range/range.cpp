#include <vector>


std::vector<int> Range(const int from, const int to, const int step = 1) {
    std::vector<int> result {};

    if (step == 0 || from == to || 
        (step > 0 && from > to) || 
        (step < 0 && from < to)) 
    {
        return result;
    }

    const size_t size { 
        (to - from) % step == 0 
        ? static_cast<size_t>((to - from) / step) 
        : static_cast<size_t>((to - from) / step) + 1
    };
    result.reserve(size);

    for (int i = from; (step > 0) ? (i < to) : (i > to); i += step) {
        result.push_back(i);
    }

    return result;
}