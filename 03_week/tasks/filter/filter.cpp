#include <stdexcept>
#include <vector>

void Filter(std::vector<int>& vec, bool (*predicate)(int)) {
    if (predicate == nullptr) {
        return;
    }

    size_t write_position = 0;
    for (size_t read_position = 0; read_position < vec.size(); ++read_position) {
        if (predicate(vec[read_position])) {
            if (write_position != read_position) {
                vec[write_position] = vec[read_position];
            }
            ++write_position;
        }
    }

    vec.resize(write_position);
}