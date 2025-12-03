#include <stdexcept>


double ApplyOperations(double a, double b, double (*ops[])(double,double), size_t size) {
    double sum = 0.0;
     for (size_t i = 0; i < size; ++i){
        sum += ops[i](a,b);
     }
    return sum;
}