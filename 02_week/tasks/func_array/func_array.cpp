#include <stdexcept>

double ApplyOperations(double a, double b, double (*func[])(double x, double y), size_t size)
{
    long double sum = 0.;
    if (func)
    {
        for (size_t i = 0; i < size; ++i)
        {
            if (*(func+i))
                sum += func[i](a, b);
        }
    }

    return sum;
}