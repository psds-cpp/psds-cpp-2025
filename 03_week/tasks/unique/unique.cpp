#include <stdexcept>
#include <vector>

std::vector<int> Unique(const std::vector <int>& vector) {

    std::vector<int> result;
    std::vector<int>::const_iterator cur_iter = vector.begin();

    if (vector.empty()) return result;  

    size_t count = 1;

    for (auto iter = vector.begin(); iter != vector.end();){

        cur_iter = iter;
        ++iter;
        
        while (iter != vector.end()) {
            if (*iter != *cur_iter) {++count; break;}
            else ++iter;
        }
    }

    result.reserve(count);

    for (auto iter = vector.begin(); iter != vector.end();){

        result.push_back(*iter);
        cur_iter = iter;
        ++iter;
        
        while (iter != vector.end() && *iter == *cur_iter) {
            ++iter;
        }
    }

    return result;
}
