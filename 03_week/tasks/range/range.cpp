#include <cmath>
#include <vector>


std::vector<int> Range(int from, int to, int step = 1) {
    std::vector<int> range{};

    if (step == 0
        || step < 0 && from < to
        || step > 0 && from > to) {
        return range;
    }

    auto absDiff = std::abs(from - to);

    range.reserve(std::ceil(std::abs(absDiff / static_cast<float>(step))));

    int val = from;
    for (size_t i = 0; i < range.capacity(); ++i) {
        range.push_back(val);
        val += step;
    }

    return range;
}
