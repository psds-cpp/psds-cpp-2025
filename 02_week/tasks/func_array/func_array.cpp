#include <stdexcept>

// Тип для указателя на функцию операции
using FuncType = double(*)(double, double);

double ApplyOperations(double a, double b, FuncType operations[], size_t size) {
    // В случае пустого массива операций возвращаем 0.0
    if (size == 0) {
        return 0.0;
    }
    
    double sum = 0.0;
    
    // Чистый цикл без использования STL алгоритмов
    for (size_t i = 0; i < size; ++i) {
        // Проверяем, что указатель на функцию не равен nullptr
        if (operations[i] != nullptr) {
            // Выполняем операцию и добавляем результат к сумме
            sum += operations[i](a, b);
        }
        // Если operations[i] == nullptr, просто пропускаем (добавляем 0 к сумме)
    }
    
    return sum;
}