#include <stdexcept>
#include <vector>

std::vector<int> Range(int from, int to, int step) {
    // Проверка на пустой диапазон
    if (step == 0) {
        // Вместо исключения возвращаем пустой вектор
        return std::vector<int>();
    }
    
    // Если шаг положительный и from >= to, или шаг отрицательный и from <= to,
    // то диапазон пустой
    if ((step > 0 && from >= to) || (step < 0 && from <= to)) {
        return std::vector<int>();
    }
    
    // Вычисляем количество элементов
    int count = 0;
    if (step > 0) {
        // Для положительного шага
        count = (to - from - 1) / step + 1;
    } else {
        // Для отрицательного шага
        count = (to - from + 1) / step + 1;
    }
    
    // Гарантируем, что count не отрицательный
    if (count <= 0) {
        return std::vector<int>();
    }
    
    // Создаем вектор с заранее выделенной памятью
    std::vector<int> result;
    result.reserve(count);
    
    // Заполняем значениями
    int current = from;
    if (step > 0) {
        while (current < to) {
            result.push_back(current);
            current += step;
        }
    } else {
        while (current > to) {
            result.push_back(current);
            current += step;  // step отрицательный, так что это вычитание
        }
    }
    
    return result;
}

std::vector<int> Range(int from, int to) {
    return Range(from, to, 1);
}