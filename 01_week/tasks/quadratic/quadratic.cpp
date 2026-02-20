#include <stdexcept>
#include <cmath>
#include <stdexcept>

void SolveQuadratic(int a, int b, int c) {
 std::cout << std::setprecision(6);
    
    // Случай бесконечных решений: 0*x² + 0*x + 0 = 0
    if (a == 0 && b == 0 && c == 0) {
        std::cout << "infinite solutions" << std::endl;
        return;
    }
    
    // Линейное уравнение: 0*x² + b*x + c = 0
    if (a == 0) {
        if (b == 0) {
            // 0*x + c = 0, где c ≠ 0 - нет решений
            std::cout << "no solutions" << std::endl;
        } else {
            // b*x + c = 0 → x = -c/b
            double x = -static_cast<double>(c) / b;
            std::cout << x << std::endl;
        }
        return;
    }
    
    // Квадратное уравнение: a*x² + b*x + c = 0, где a ≠ 0
    double discriminant = static_cast<double>(b) * b - 4.0 * a * c;
    
    if (discriminant < 0) {
        // Отрицательный дискриминант - нет действительных корней
        std::cout << "no solutions" << std::endl;
    } else if (discriminant == 0) {
        // Нулевой дискриминант - один корень
        double x = -static_cast<double>(b) / (2.0 * a);
        std::cout << x << std::endl;
    } else {
        // Положительный дискриминант - два корня
        double sqrt_d = std::sqrt(discriminant);
        double x1 = (-b - sqrt_d) / (2.0 * a);
        double x2 = (-b + sqrt_d) / (2.0 * a);
        
        // Убеждаемся, что x1 < x2
        if (x1 > x2) {
            std::swap(x1, x2);
        }
        
        std::cout << x1 << " " << x2 << std::endl;
    }
}