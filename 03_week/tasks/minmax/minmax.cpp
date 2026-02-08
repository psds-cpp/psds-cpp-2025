#include <stdexcept>
#include <bits/stdc++.h>

using citer = std::vector<int>::const_iterator;

std::pair<citer, citer> MinMax(const std::vector<int>& vec) {
    if (vec.empty())
        return {vec.end(), vec.end()};

    auto minEl = vec.begin();
    auto maxEl = vec.begin(); 

    for (auto x = vec.begin(); x != vec.end(); ++x) {
        if (*x < *minEl)
            minEl = x;
        if (*x >= *maxEl) 
            maxEl = x;
    }

    return {minEl, maxEl};
}
