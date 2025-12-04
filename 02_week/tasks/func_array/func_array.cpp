#include <stdexcept>


double ApplyOperations(
    double a,
    double b,
    double (*operations[])(double, double),
    size_t size
) {
    if (size == 0) {
        return 0.0;
    }

    double sum = 0.0;

    for (size_t i = 0; i < size; ++i) {

        // ---- ключевая защита ----
        if (operations[i] == nullptr) {
            continue; // пропускаем пустую функцию
        }

        double value = operations[i](a, b);
        sum += value;
    }

    return sum;
}