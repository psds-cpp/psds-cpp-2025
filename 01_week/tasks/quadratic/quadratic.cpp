#include <cmath>
#include <stdexcept>
#include <iomanip>
#include <bits/stdc++.h>


void SolveQuadratic(int a, int b, int c) {
    if (a == 0 && b == 0 && c == 0)
        std::cout << "infinite solutions";
    else if (a == 0 && b == 0 && c != 0)
        std::cout << "no solutions";
    else if (a == 0 && b != 0 && c == 0)
        std::cout << "0";
    else if (a == 0 && b != 0 && c != 0)
        std::cout << std::setprecision(6) << static_cast<long double>(-c) / static_cast<long double>(b);
    else if (a != 0 && b == 0 && c == 0)
        std::cout << "0";
    else if (a != 0 && b == 0 && c != 0) {
        if (c > 0)
            std::cout << "no solutions";
        else {
            long double x = sqrt(static_cast<long double>(-c) / static_cast<long double>(a));
            std::cout << std::setprecision(6) << -x << ' ' << x;
        }   
    }
    else if (a != 0 && b != 0 && c == 0) {
        long double x = static_cast<long double>(-b) / static_cast<long double>(a);
        if (x < 0)
            std::cout << std::setprecision(6) << x << " 0";
        else
            std::cout << std::setprecision(6) << "0 " << x;
    }
    else {
        long long d = (long long)b*b - 4LL*a*c;
        if (d < 0)
            std::cout << "no solutions";
        else if (d == 0)
            std::cout << std::setprecision(6) << static_cast<long double>(-b) / (2.0L*a);
        else {
            long double sqrtd = sqrt(d);
            long double x1 = (static_cast<long double>(-b) + sqrtd) / (2.0L*a);
            long double x2 = (static_cast<long double>(-b) - sqrtd) / (2.0L*a);
            if (x1 < x2)
                std::cout << std::setprecision(6) << x1 << ' ' << x2;
            else
                std::cout << std::setprecision(6) << x2 << ' ' << x1;
        }
    }
}