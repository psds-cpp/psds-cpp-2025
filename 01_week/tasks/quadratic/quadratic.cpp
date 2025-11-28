#include <iomanip>
#include <iostream>
#include <cmath>


void SolveQuadratic(int a, int b, int c) {
    double a_db = static_cast<double>(a);
    double b_db = static_cast<double>(b);
    double c_db = static_cast<double>(c);

    if (!a && !b && !c) {
        std::cout << "infinite solutions";
        return;
    }

    if (a == 0) {
        b_db != 0 ? std::cout << -(c_db / b_db) : std::cout << "no solutions";
        return;
    }

    if (b == 0 && c == 0) {
        std::cout << 0;
        return;
    }

    double discriminant = b_db*b_db - 4*a_db*c_db;

    if (discriminant > 0) {
        double x1 = (-b_db - sqrt(discriminant)) / (2 * a_db);
        double x2 = (-b_db + sqrt(discriminant)) / (2 * a_db);
        std::cout << std::setprecision(6) << x1 << ' ' << x2;
    }
    else if (discriminant == 0) {
        double x = -b_db / (2 * a_db);
        std::cout << std::setprecision(6) << x;
    }
    else {
        std::cout << "no solutions";
    }
}