#include <vector>

using Predicate = bool (*)(int);

void Filter(std::vector<int>& vec, Predicate predicate) {
    
    if (!predicate) {
        return;
    }
    
    size_t write_index = 0;
    
    for (size_t read_index = 0; read_index < vec.size(); ++read_index) {
        if (predicate(vec[read_index])) {
                if (write_index != read_index) {
                vec[write_index] = vec[read_index];
            }
            ++write_index;
        }
    }
    
    vec.resize(write_index);
}