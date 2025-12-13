#include <stdexcept>
#include <bits/stdc++.h>


double CalculateRMS(double values[], size_t size) {
    if (size == 0 || values == nullptr)
        return 0.0;
    long double sum = 0.0L;
    for (size_t i = 0; i < size; ++i)
        sum += values[i] * values[i];
    sum /= size;
    return sqrt(sum);
}