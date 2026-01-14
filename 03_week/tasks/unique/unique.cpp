#include <stdexcept>
#include <vector>

std::vector<int> Unique(const std::vector<int>& vec) {
    std::vector<int> result;
    if (vec.empty()) return result;
    result.reserve(vec.size()); // выделяем кол-во памяти неменьше чем для vec
    result.push_back(vec[0]);  // заполняем первым элементом
    size_t write_index = 0; // блуждающий индекс для вектора result
    for (size_t i = 1; i < vec.size(); ++i) {
        if (result[write_index] != vec[i]){ // если следующий элемент не равен предыдущему то добавляем его в result
            result.push_back(vec[i]);
            ++write_index;
        }
    }
    ++write_index; // Костыль чтобы учесть первый добавленный элемент
    result.shrink_to_fit(); // обрезаем лишнюю память
    return result;
}
