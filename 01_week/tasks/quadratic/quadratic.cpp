#include <stdexcept>
#include <iomanip>
#include <iostream>

void SolveQuadratic(int a, int b, int c) {
    float x1 = 0.0; // Превый корень уравнения
    float x2 = 0.0; // Второй корень уравнения.
    
    float fA = static_cast<float>(a);   // Явное приведение типа int к float
    float fB = static_cast<float>(b);   // Явное приведение типа int к float
    float fC = static_cast<float>(c);   // Явное приведение типа int к float
    float disc = static_cast<float>(c); // Явное приведение типа int к float
    float negativeUnit = -1;            // Защита для формул при умножении на -1
    
    // Если a, b, c равны нулю – решений бесконечно много.
    if((a == 0) && (b == 0) && (c == 0)){
        std::cout <<"infinite solutions";
        return;
    }
    
    // Если a, b равны нулю – решений а не равно нулю –решений нет!
    if((a == 0) && (b == 0) && (c != 0))
    {
        std::cout <<"no solutions";
        return;
    }
    
    // Если x = 0 
    if(((a == 0) && (c == 0)) || ((b == 0) && (c == 0)))
    {
        std::cout <<"0";
        return;
    }
    
    
    if(a == 0)  // Своего рода ускорение вычисления при a равном нулю
    {
        x1 = (-fC)/fB;
        std::cout << std::setprecision(6) << x1;
    }
    else    // Решение через дискрименант
    {
        disc = fB * fB - 4 * fA * fC;
        
        if(disc < 0)
        {
            std::cout <<"no solutions";
            return;
        }
        
        x1 = (negativeUnit * fB - sqrt(disc))/(2*fA);
        x2 = (negativeUnit * fB + sqrt(disc))/(2*fA);
        
        // определяем вывод в зависимости от X1 и X2
        if (x1 == x2)    std::cout << std::setprecision(6) << x1 ;
        else if(x1 < x2) std::cout << std::setprecision(6) << x1 << ' ' << x2;
        else             std::cout << std::setprecision(6) << x2 << ' ' << x1;
        
        return;
    }
