#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>

void SolveQuadratic(int a, int b, int c) {
    // a,b,c=0
    if (a == 0 && b == 0 && c == 0) {
        std::cout << "infinite solutions";
        return;
    }
    
    // a=0
    if (a == 0) {
        if (b == 0) {
            // c=0
            if (c == 0) {
                std::cout << "infinite solutions";
            } else {
                std::cout << "no solutions";
            }
        } else {
            // b*x+c=0
            double x = -static_cast<double>(c) / b;
            // Обработка случая -0.0
            if (std::abs(x) < 1e-10) x = 0.0;
            std::cout << std::setprecision(6) << x;
        }
        return;
    }
    
    // Вычисление D
    double discriminant = static_cast<double>(b) * b - 4.0 * a * c;
    
    if (discriminant < 0) {
        // D<0
        std::cout << "no solutions";
    } else if (discriminant == 0) {
        // D=0
        double x = -static_cast<double>(b) / (2.0 * a);
        // Обработка случая -0.0
        if (std::abs(x) < 1e-10) x = 0.0;
        std::cout << std::setprecision(6) << x;
    } else {
        // D>0
        double sqrt_d = std::sqrt(discriminant);
        double x1 = (-b - sqrt_d) / (2.0 * a);
        double x2 = (-b + sqrt_d) / (2.0 * a);
        
        // Обработка случая -0.0 для обоих корней
        if (std::abs(x1) < 1e-10) x1 = 0.0;
        if (std::abs(x2) < 1e-10) x2 = 0.0;
        
        if (x1 > x2) {
            std::swap(x1, x2);
        }
        
        std::cout << std::setprecision(6) << x1 << " " << x2;
    }
}