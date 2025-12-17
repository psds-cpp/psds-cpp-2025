#include <vector>


void Filter(std::vector<int>& vec, bool (*predicate)(int)) {
    if (vec.empty() || predicate == nullptr) {
        return;
    }
    
    size_t write {}; // куда писать "валидные" элементы
    for (std::size_t read = 0; read < vec.size(); ++read) {
        if (predicate(vec[read])) {
            vec[write++] = vec[read];
        }
    }
    vec.resize(write); // обрезаем хвост
}