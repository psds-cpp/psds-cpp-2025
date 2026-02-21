#include <cmath>
#include <stdexcept>
#include <iomanip>
#include <bits/stdc++.h>


void SolveQuadratic(int a, int b, int c) {
    if (a == 0) {
        if (b == 0) {
            std::cout << (c == 0 ? "infinite solutions" : "no solutions");
        }
        else {
            std::cout << std::setprecision(6) << static_cast<long double>(-c) / b;
        }
        return;
    }
    
    long long d = static_cast<long long>(b) * b - 4LL * a * c;

    if (d < 0) {
        std::cout << "no solutions";
        return;
    }

    if (d == 0) {
        std::cout << std::setprecision(6) << static_cast<long double>(-b) / (2.0L * a);
        return;
    }

    long double sqrtd = std::sqrt(static_cast<long double>(d));
    long double x1 = (-b - sqrtd) / (2.0L * a);
    long double x2 = (-b + sqrtd) / (2.0L * a);

    if (x1 > x2) std::swap(x1, x2);
    
    std::cout << std::setprecision(6) << x1 << ' ' << x2;
}