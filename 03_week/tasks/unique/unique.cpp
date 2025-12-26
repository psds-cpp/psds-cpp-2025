#include <stdexcept>
#include <vector>

std::vector<int> Unique(const std::vector<int>& vec) {
    if (vec.size() == 0) return std::vector<int>();
    
    std::vector<int> unique_vec(vec.size() / 2);
    size_t unique_ind = 0;
    bool the_first_elem = true;

    for (size_t i = 0; i < vec.size(); ++i) {
        if (unique_vec.size() == unique_ind) 
            unique_vec.resize(unique_vec.size() * 2);

        if (the_first_elem || vec[i] != vec[i - 1]) {
            if (unique_vec.empty()) unique_vec.push_back(vec[i]);
            else unique_vec[unique_ind] = vec[i];
            ++unique_ind;
            the_first_elem = false;
        } 
    }
    
    unique_vec.erase(unique_vec.begin() + unique_ind, unique_vec.end());
    unique_vec.shrink_to_fit();

    return unique_vec;
}