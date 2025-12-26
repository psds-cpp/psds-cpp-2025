#include <stdexcept>
#include <vector>


std::vector<int> Range(int from, int to, int step = 1) {
    if ((from <= to && step < 0) || (from >= to && step > 0) || step == 0)
        return {};

    int cnt = (to - from) / step;
    if ((to - from) % step != 0)
        ++cnt;

    std::vector<int> result;
    result.reserve(cnt);

    for (int el = from; (step > 0 ? el < to : el > to); el += step)
        result.push_back(el);

    return result;
}
