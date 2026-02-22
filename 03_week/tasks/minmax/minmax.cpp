#include <vector>

typedef std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator> MinMaxIter;

MinMaxIter MinMax(const std::vector<int>& arr) {
    auto first = arr.begin(), last = arr.end();

    if (first == last)
        return {last, last};

    auto min = first, max = first;

    while (++first != last) {
        auto i = first;
        if (++first == last) {
            min = (*i < *min) ? i : min;
            max = (*i >= *max) ? i : max;
            break;
        }

        auto smaller = (*first < *i) ? first : i;
        auto larger = (*first < *i) ? i : first;

        min = (*smaller < *min) ? smaller : min;
        max = (*larger >= *max) ? larger : max;
    }

    return {min, max};
}
