#include <stdexcept>
#include <vector>
#include <algorithm>
#include <iostream>

std::vector<int> Range(int from, int to, int step = 1) {
    if ((from <= to && step < 0) || (from >= to && step > 0) || step == 0)
        return {};

    int count = (to - from) / step;
    if ((to - from) % step != 0)
        ++count;

    std::vector<int> result;
    result.reserve(count);

    for (int el = from; (step > 0 ? el < to : el > to); el += step)
        result.push_back(el);

    return result;
}


int main(void) {
    std::vector<int> res = Range(20, 20, 3);

    for (size_t i = 0; i < res.size(); ++i) {
        std::cout << res[i] << ' ';
    }
    std::cout << '\n';
    return 0;
}