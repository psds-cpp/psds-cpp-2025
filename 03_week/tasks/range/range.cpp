#include <stdexcept>
#include <vector>


std::vector<int> Range(int from, int to, int step = 1) {
    std::vector <int> range;
    if ((to - from) * step <= 0){
        return range;
    }
    
    range.reserve(abs(to - from) / abs(step) + abs(to - from) % abs(step));
    for (int i = from; (to - i) * step > 0; i += step){
        range.push_back(i);
    }
    return range;
}
