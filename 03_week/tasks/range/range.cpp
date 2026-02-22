#include <vector>
#include <math.h>


std::vector<int> Range(int from, int to, const int step = 1) {
    std::vector<int> result{};
    result.reserve(std::abs(from - to));

    while ((from > to && step < 0) || (from < to && step > 0)) {
        result.push_back(from);
        from += step;
    }

    result.shrink_to_fit();
    return result;
}
