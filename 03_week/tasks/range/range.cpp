#include <stdexcept>
#include <vector>


std::vector<int> Range(int from, int to, int step = 1) {
    std::vector<int> result;
    if ((to - from)*step <= 0) return result; // проверка на невалидные параметры
    size_t size = (step > 0) ? ((to - from - 1)/step + 1) : ((from - to - 1)/(-step) + 1); // определим кол-во элементов которое необходимо выделить для вектора

    result.reserve(size); // выделяем память под кол-во элементов size
    for (size_t i = 0; i < size; ++i){
        result.push_back(from + i * step);
    }
    return result;
}
