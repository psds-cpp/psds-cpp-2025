#include <iostream>
#include <iomanip>
#include <cmath>

void SolveQuadratic(int a, int b, int c) {
    std::streamsize precision = std::cout.precision();
    std::ios_base::fmtflags flags = std::cout.flags();

    std::cout << std::setprecision(6);

    if (a == 0) {
        if (b == 0) {
            if (c == 0) {
                std::cout << "infinite solutions";
            }
            else {
                std::cout << "no solutions";
            }
        }
        else {
            double x = (double)(-c) / b;
            std::cout << x;
        }
    }
    else {
        double D = b*b - 4*a*c;

        if (D == 0) {
            double x = -b / (2.0*a);
            std::cout << x;
        }
        else if (D > 0) {
            double x1 = (-b - std::sqrt(D)) / (2.0*a);
            double x2 = (-b + std::sqrt(D)) / (2.0*a);
            std::cout << x1 << " " << x2;
        }
        else {
            std::cout << "no solutions";
        }
    }

    std::cout.precision(precision);
    std::cout.flags(flags);
}
