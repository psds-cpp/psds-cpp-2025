#include <iostream>
#include <iomanip>
#include <cmath>
#include <utility>

void SolveQuadratic(int a, int b, int c) {
    std::cout << std::setprecision(6);
    
    if (a == 0 && b == 0 && c == 0) {
        std::cout << "infinite solutions";
        return;
    }
    
    if (a == 0 && b == 0 && c != 0) {
        std::cout << "no solutions";
        return;
    }
    
    if (a == 0) {
        double root = -static_cast<double>(c) / b;
        
        if (root == 0.0) root = 0.0;
        
        std::cout << root;
        return;
    }
    
    double discr = static_cast<double>(b) * b - 4.0 * a * c;
    
    if (discr < 0) {
        std::cout << "no solutions";
        return;
    }
    
    if (discr == 0) {
        double root = -static_cast<double>(b) / (2.0 * a);
        
        if (root == 0.0) root = 0.0;
        
        std::cout << root;
        return;
    }
    
    double sqrt_d = std::sqrt(discr);
    double root1 = (-static_cast<double>(b) - sqrt_d) / (2.0 * a);
    double root2 = (-static_cast<double>(b) + sqrt_d) / (2.0 * a);
    
    if (root1 > root2) {
        std::swap(root1, root2);
    }
    
    if (root1 == 0.0) root1 = 0.0;
    if (root2 == 0.0) root2 = 0.0;
    
    std::cout << root1 << " " << root2;
}