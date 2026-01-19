#include <vector>
#include <stdexcept>


void Filter(std::vector<int>& vec, bool(*pred)(int)) {

    if (pred == nullptr) {
        return; 
    }

    size_t write_ptr = 0;
    
    for (size_t read_ptr = 0; read_ptr < vec.size(); ++read_ptr) {
        if (pred(vec[read_ptr])) {
            vec[write_ptr] = vec[read_ptr];
            ++write_ptr;
        }
    }
    vec.resize(write_ptr);
}