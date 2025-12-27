#include <vector>

std::vector<int> Range(int from, int to, int step = 1) {
    if (step == 0) {
        return std::vector<int>();
    }

    if ((step > 0 && from >= to) || (step < 0 && from <= to)) {
        return std::vector<int>();
    }

    int count;
    if (step > 0) {
        count = (to - from + step - 1) / step;
    } else {
        count = (to - from + step + 1) / step;
    }

    std::vector<int> result;
    result.reserve(count);

    bool isForward = step > 0;
    for (int i = from; isForward ? (i < to) : (i > to); i += step) {
        result.push_back(i);
    }

    return result;
}