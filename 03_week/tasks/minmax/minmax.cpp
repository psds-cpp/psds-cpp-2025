#include <stdexcept>
#include <vector>

using IntVecIterator = std::vector<int>::const_iterator;

std::pair<IntVecIterator, IntVecIterator> MinMax(const std::vector<int>& numbers) {
    if (numbers.empty()) {
        return {numbers.end(), numbers.end()};
    }

    IntVecIterator min_it = numbers.begin();
    IntVecIterator max_it = numbers.begin();

    auto it = numbers.begin() + 1;
    const auto last = numbers.end();

    while (it + 1 < last) {
        IntVecIterator a = it;
        IntVecIterator b = it + 1;

        IntVecIterator local_min, local_max;
        if (*a <= *b) {
            local_min = a;
            local_max = b;
        } else {
            local_min = b;
            local_max = a;
        }

        if (*local_min < *min_it) min_it = local_min;
        if (*local_max >= *max_it) max_it = local_max;

        it += 2;
    }

    if (it != last) {
        if (*it < *min_it) {
            min_it = it;
        } else if (*it >= *max_it) {
            max_it = it;
        }
    }

    return {min_it, max_it};
}
