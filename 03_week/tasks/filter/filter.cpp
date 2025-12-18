#include <stdexcept>
#include <vector>


void Filter(std::vector<int>& vec, bool (*pred_func) (int)) {
    if (!pred_func) return;
    size_t write_index = 0;
    for (size_t i = 0; i < vec.size(); ++i) {
        if (pred_func(vec[i])) {
            vec[write_index] = vec[i];
            ++write_index;
        }
    }
    vec.resize(write_index);
}
