#include <vector>

std::vector<int> Unique(const std::vector<int>& data) {
    std::vector<int> res;
    if(data.empty()) return res;

    res.reserve(data.size());
    res.push_back(data[0]);
    for(auto el : data){
        if(res.back() != el) res.push_back(el);
    }
    res.shrink_to_fit();
    return res;
}
