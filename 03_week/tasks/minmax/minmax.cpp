#include <vector>


std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator> MinMax(const std::vector<int>& arr) {
    auto first = arr.begin(), last = arr.end();

    if (first == last)
        return {last, last};

    auto min = first, max = first;

    while (++first != last) {
        auto i = first;
        if (++first == last) {
            if (*i < *min)
                min = i;
            else if (*i >= *max)
                max = i;
            break;
        }
        else {
            if (*first < *i) {
                if (*first < *min)
                    min = first;
                if (*i >= *max)
                    max = i;
            }
            else {
                if (*i < *min)
                    min = i;
                if (*first >= *max)
                    max = first;
            }
        }
    }

    return {min, max};
}
