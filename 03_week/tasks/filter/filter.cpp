#include <stdexcept>
#include <vector>


std::vector<int> Filter(std::vector<int>& vec, bool (*func) (int)) {
    if (vec.empty() or func == nullptr){
        return vec;
    }
    auto it_rez = vec.begin();
    size_t len = 0;
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        if (func(*it)){
            *it_rez = *it;
            it_rez += 1;
            len += 1;
        }
    }
    vec.resize(len);
    return vec;
}

