#include <cmath>
#include <iomanip>
#include <iostream>

// Уверен, что это можно сделать значительно качественнее, но дедлайн близко,
// поэтому спагетти код >:)

void SolveQuadratic(int a, int b, int c) { 
    if (a == 0 && b == 0 && c == 0) {
        std::cout << "infinite solutions";
        return;
    }
    
    if (a == 0 && b == 0) {
        std::cout << "no solutions";
        return;
    }

    std::cout << std::setprecision(6);

    if (a == 0) {
        std::cout << static_cast<double>(-c) / b;
        return;
    }

    if (b == 0) {
        if (static_cast<double>(-c) / a < 0) {
            std::cout << "no solutions";
            return;
        }

        double root = std::sqrt(static_cast<double>(-c) / a);
        
        if (root == 0) {
            std::cout << root;
        } else {
            std::cout << -root << " " << root;
        }
        
        return;
    }

    double discriminant = static_cast<double>(b) * b - 4.0 * a * c;
    double root1 = 0.0, root2 = 0.0;

    if (discriminant == 0) {
        std::cout << -b / (2.0 * a);    
    }

    if (discriminant < 0) {
        std::cout << "no solutions";
        return;
    }

    root1 = ((-b - std::sqrt(discriminant)) / (2.0 * a));
    root2 = ((-b + std::sqrt(discriminant)) / (2.0 * a));

    root1 > root2 ? std::cout << root2 << " " << root1 :
                  std:: cout << root1 << " " << root2;
}
