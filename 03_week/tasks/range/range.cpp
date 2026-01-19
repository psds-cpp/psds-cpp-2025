#include <stdexcept>
#include <vector>

std::vector<int> Range(int from, int to, int step) {
    if (step == 0) {
        return std::vector<int>();
    }
    
    if ((step > 0 && from >= to) || (step < 0 && from <= to)) {
        return std::vector<int>();
    }
    
    int count = 0;
    if (step > 0) {
        count = (to - from - 1) / step + 1;
    } else {
        count = (to - from + 1) / step + 1;
    }
    
    if (count <= 0) {
        return std::vector<int>();
    }
    
    std::vector<int> result;
    result.reserve(count);
    
    int current = from;
    if (step > 0) {
        while (current < to) {
            result.push_back(current);
            current += step;
        }
    } else {
        while (current > to) {
            result.push_back(current);
            current += step;  
        }
    }
    
    return result;
}

std::vector<int> Range(int from, int to) {
    return Range(from, to, 1);
}