#include <cstddef>
#include <stdexcept>


double CalculateRMS(double values[], size_t size) {
    double sum = 0.0;
    
    if(0 == size) return 0.0;//
    if(&values[0] == nullptr) return 0.0;
    
    for(size_t i = 0; i < size; i++){
        sum += values[i]*values[i];
    }
    
    return std::sqrt(sum / size);
}
