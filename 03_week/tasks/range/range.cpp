#include <stdexcept>
#include <vector>


std::vector<int> Range(int from, int to, int step = 1) {
    int size = 0;
    if(from == to || (from > to && step > 0) || (from < to && step < 0) || step == 0) {
        return {};
    }
    if ((step > 0 && from < to) || (step < 0 && from > to)) {
        size = (std::abs(to - from) + std::abs(step) - 1) / std::abs(step);
    }
    std::vector<int> sequence;
    sequence.reserve(size);

    int current = from;
    if (step > 0) {
        while (current < to) {
            sequence.push_back(current);
            current += step;
        }
    } else {
        while (current > to) {
            sequence.push_back(current);
            current += step;
        }
    }

    return sequence;
}
