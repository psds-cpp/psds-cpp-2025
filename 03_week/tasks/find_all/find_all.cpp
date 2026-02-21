#include <cstddef>
#include <stdexcept>
#include <bits/stdc++.h>

std::vector<size_t> FindAll(const std::vector<int>& vec, bool (*func)(int)) {
    if (func == nullptr)
        return {};
 
    size_t count = 0;
    for (size_t i = 0; i < vec.size(); ++i)
        if (func(vec[i]))
            ++count;
    std::vector<size_t> result(count);

    size_t pos = 0;
    size_t len = vec.size();
    for (size_t i = 0; i < len; ++i)
        if (func(vec[i]))
            result[pos++] = i;

    return result;
}