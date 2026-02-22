#include <stdexcept>
#include <iomanip>
#include <iostream>
#include <cmath>


void SolveQuadratic(int a, int b, int c) {
    if (a == 0 && b != 0) { // проверяем уникальные случаи коэффициентов
        double x1 = static_cast<double>(-c)/b;
        std::cout << std::setprecision(6) << x1;
        return;
    }
    if (a == 0 && b == 0 && c != 0) {
        std::cout << "no solutions";
        return;
    }
    if (a == 0 && b == 0 && c == 0) {
        std::cout << "infinite solutions";
        return;
    }
//Проверяем дискрименант
    double D = b*b-4*a*c;
    if (D > 0){
        double x1 = (-b - std::sqrt(D))/(2*a);
        double x2 = (-b + std::sqrt(D))/(2*a);
        std::cout << std::setprecision(6) << x1 << " " << x2;
        return;
    }
    if (D == 0){
        double x1 = static_cast<double>(-b)/(2*a);
        std::cout << std::setprecision(6) << x1;
        return;
    }
    if (D < 0){
        std::cout << "no solutions";
        return;
    }
}
