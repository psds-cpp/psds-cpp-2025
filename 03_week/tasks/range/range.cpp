#include <stdexcept>
#include <vector>


std::vector<int> Range(int from, int to, int step=1) {

    std::vector<int> result;

    if ((step == 0) || (from > to && step>0) || (from < to && step<0)) return result;

    size_t size_of_result = step > 0 ? (to - from + step - 1) / step : (from - to - step - 1) / (-step);
    result.resize(size_of_result);
    size_t cur_idx = 0;

    for (int i=from; step>0 ? i < to : i > to; i+=step){
        result[cur_idx] = i;
        ++cur_idx;
    }

    return result;
}
