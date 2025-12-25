#include <iostream>
#include <iomanip>
#include <cmath>


void SolveQuadratic(int a, int b, int c) {
    // первый случай: если a = b = c = 0, то уравнение примнимает бесконченое количесвто решений
    if (a == 0 && b == 0 && c == 0) {
        std::cout << "infinite solutions";
        return;
    }

    // второй случай: если a = b = 0, то уравнение решений не имеет
    if (a == 0 && b == 0) {
        std::cout << "no solutions";
        return;
    }

    std::cout << std::setprecision(6);

    // третий случай: a == 0, b != 0 → b*x + c = 0
    if (a == 0) {
        double x = -static_cast<double>(c) / static_cast<double>(b); // x = -c / b

        // Убираем возможный "-0"
        if (x == -0.0) {
            x = 0.0;
        }

        std::cout << x;
        return;
    }

    // 4) четвертый случай: a неравно 0, то есть уже само квадартное уравнение
    double A = static_cast<double>(a);
    double B = static_cast<double>(b);
    double C = static_cast<double>(c);

    // Дискриминант
    double D = B * B - 4 * A * C;

    // Нет вещественных корней
    if (D < 0) {
        std::cout << "no solutions";
        return;
    }

    // Один вещественный корень
    if (D == 0) {
        double root = -B / (2 * A);
        double x = static_cast<double>(root);

        // Убираем "-0"
        if (x == -0.0) {
            x = 0.0;
        }

        std::cout << x;
        return;
    }

    // если D > 0, то имеем два различных корня
    double sqrtD = std::sqrt(D);

    double root1 = (-B - sqrtD) / (2 * A); 
    double root2 = (-B + sqrtD) / (2 * A);

    double x1 = static_cast<double>(root1);
    double x2 = static_cast<double>(root2);

    // Убираем "-0" для каждого корня
    if (x1 == -0.0) {
        x1 = 0.0;
    }
    if (x2 == -0.0) {
        x2 = 0.0;
    }

    // выводим так, чтобы x1 < x2
    if (x1 > x2) {
        std::swap(x1, x2);
    }

    std::cout << x1 << ' ' << x2;
}
