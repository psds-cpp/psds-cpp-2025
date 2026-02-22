#include <iomanip>
#include <iostream>
#include <cmath>


void SolveQuadratic(int a, int b, int c) {
    if (a == 0 && b == 0 && c == 0) {
        std::cout << "infinite solutions";
        return;
    }

    if (a == 0) {
        b != 0 ? std::cout << -(static_cast<double>(c) / b) : std::cout << "no solutions";
        return;
    }

    if (b == 0 && c == 0) {
        std::cout << 0;
        return;
    }

    double discriminant = static_cast<double>(b) * b - 4.0 * a * c;

    if (discriminant > 0) {
        double sqrt_d = std::sqrt(discriminant);
        double x1 = (-b - sqrt_d) / (2.0 * a);
        double x2 = (-b + sqrt_d) / (2.0 * a);
        std::cout << std::setprecision(6) << x1 << ' ' << x2;
    }
    else if (discriminant == 0) {
        double x = -b / (2.0 * a);
        std::cout << std::setprecision(6) << x;
    }
    else {
        std::cout << "no solutions";
    }
}