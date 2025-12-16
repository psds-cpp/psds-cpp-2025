#include <stdexcept>
#include <vector>

void Filter(std::vector<int>& vector, bool (*func)(int)) {
    size_t index_good = 0;
    
    for (size_t i = 0; i < vector.size(); ++i) {
        if ((func) && (!func(vector[i]))) {
            continue;
        }
        else {
            vector[index_good] = vector[i];
            ++index_good;
        }
    }
    
    vector.resize(index_good);
}