#include <stdexcept>
#include <vector>

std::vector<int> Range(int from, int to, int step) {
        if (step == 0) {
        return {};
    }
    
    if ((step > 0 && from >= to) || (step < 0 && from <= to)) {
        return {};
    }
    
    int n = 0;
    if (step > 0) {
        n = (to - from - 1) / step + 1;
    } else {
        n = (to - from + 1) / step + 1;
    }
   
    std::vector<int> result;
    result.reserve(n);
    
    int current = from;
    while ((step > 0 && current < to) || (step < 0 && current > to)) {
        result.push_back(current);
        current += step;
    }
    
    return result;
}

std::vector<int> Range(int from, int to) {
    return Range(from, to, 1);
}