#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>

void SolveQuadratic(int a, int b, int c) {
    std::cout << std::defaultfloat << std::setprecision(6);
    
    if (a == 0 && b == 0 && c == 0) {
        std::cout << "infinite solutions";
        return;
    }
    
    if (a == 0) {
        if (b == 0) {
            std::cout << "no solutions";
        }
        else {
            double x = -static_cast<double>(c) / b;
            if (x == -0) {
                x = 0;
            }
            std::cout << x;
        }
        return;
    }
    
    double discriminant = static_cast<double>(b) * b - 4.0 * a * c;
    if (discriminant < 0) {
        std::cout << "no solutions";
    }
    else if (discriminant == 0) {
        double x = -static_cast<double>(b) / (2.0 * a);
        if (x == -0) {
            x = 0;
        }
        std::cout << x;
    }
    else {
        double sqrt_d = std::sqrt(discriminant);
        double x1 = (-static_cast<double>(b) - sqrt_d) / (2.0 * a);
        double x2 = (-static_cast<double>(b) + sqrt_d) / (2.0 * a);
        
        if (x1 > x2) {
            std::swap(x1, x2);
        }

        std::cout << x1 << " " << x2;
    }
}
