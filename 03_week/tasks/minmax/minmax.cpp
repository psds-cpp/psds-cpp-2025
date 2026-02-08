#include <vector>
#include <stdexcept>
#include <utility>

// Неконстантная версия (возвращает итераторы, позволяющие изменять элементы)
std::pair<std::vector<int>::iterator, std::vector<int>::iterator> 
MinMax(std::vector<int>& vec) {
    if (vec.empty()) {
        return {vec.end(), vec.end()};
    }
    
    auto min_it = vec.begin();
    auto max_it = vec.begin();
    
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        if (*it < *min_it) {
            min_it = it;
        }
        else if (*it >= *max_it) {
            max_it = it;
        }
    }
    
    return {min_it, max_it};
}

// Константная версия (для работы с const vector)
std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator> 
MinMax(const std::vector<int>& vec) {
    if (vec.empty()) {
        return {vec.cend(), vec.cend()};
    }
    
    auto min_it = vec.cbegin();
    auto max_it = vec.cbegin();
    
    for (auto it = vec.cbegin(); it != vec.cend(); ++it) {
        if (*it < *min_it) {
            min_it = it;
        }
        else if (*it >= *max_it) {
            max_it = it;
        }
    }
    
    return {min_it, max_it};
}


// using Iterator = std::vector<int>::iterator;

// std::pair<Iterator, Iterator> MinMax(std::vector<int>& v) {
//     if (v.empty()) {
//         return {v.end(), v.end()};
//     }
    
//     auto min_it = v.begin();    // обычный iterator
//     auto max_it = v.begin();
    
//     for (auto it = v.begin() + 1; it != v.end(); ++it) {
//         if (*it <= *min_it) {
//             min_it = it;
//         } else if (*it >= *max_it) {
//             max_it = it;
//         }
//     }
    
//     return {min_it, max_it};
// }

