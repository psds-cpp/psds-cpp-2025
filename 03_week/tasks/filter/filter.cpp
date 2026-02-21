#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <bits/stdc++.h>


std::vector<int>& Filter(std::vector<int>& vec, bool (*func)(int)) {
    if (func == nullptr)
        return vec;

    size_t pos = 0;
    size_t len = vec.size();
    for (size_t i = 0; i < len; ++i)
        if (func(vec[i]))
            vec[pos++] = vec[i];
        
    vec.resize(pos);
    return vec;
}