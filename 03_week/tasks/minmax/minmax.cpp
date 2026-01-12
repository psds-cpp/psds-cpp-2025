#include <stdexcept>
#include <vector>
#include <utility>

std::pair <std::vector<int>::iterator, std::vector<int>::iterator> MinMax(std::vector<int>& vec) {
    std::pair<std::vector<int>::iterator, std::vector<int>::iterator> rez;
    if (vec.begin() == vec.end()){
        rez.first = vec.begin();
        rez.second = vec.begin();
        return rez;
    }
    auto min_it = vec.begin();
    auto max_it = vec.begin();
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        if (*it < *min_it){
            min_it = it;
        }
        if (*it >= *max_it){
            max_it = it;
        }
    }
    
    rez.first = min_it;
    rez.second = max_it;
    return rez;
}

std::pair <std::vector<int>::const_iterator, std::vector<int>::const_iterator> MinMax(const std::vector<int>& vec) {
    std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator> rez;
    if (vec.begin() == vec.end()){
        rez.first = vec.begin();
        rez.second = vec.begin();
        return rez;
    }
    auto min_it = vec.begin();
    auto max_it = vec.begin();
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        if (*it < *min_it){
            min_it = it;
        }
        if (*it >= *max_it){
            max_it = it;
        }
    }
    
    rez.first = min_it;
    rez.second = max_it;
    return rez;
}