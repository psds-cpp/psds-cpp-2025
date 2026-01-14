#include <stdexcept>
#include <iostream>


double ApplyOperations(double a, double b, double (*func[])(double, double), size_t size) {
    if (size == 0){
        return 0.0;
    }

    double result = 0;
    for (size_t i = 0; i < size; ++i) {
        if (func[i] == nullptr){
            result += 0.0;
            continue;
        }
        result += func[i](a,b);
    }
    return result;
}
