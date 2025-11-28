#include <cmath>

double operator "" __ft_to_m(long double value) {
    return static_cast<double>(value * 0.3048);
}

double operator "" _ft_to_cm(long double value) {
    return static_cast<double>(value * 30.48);
}

double operator "" _ft_to_in(long double value) {
    return static_cast<double>(value * 12.0);
}

double operator "" _in_to_m(long double value) {
    return static_cast<double>(value * 0.0254);
}

double operator "" _in_to_cm(long double value) {
    return static_cast<double>(value * 2.54);
}

double operator "" _in_to_ft(long double value) {
    return static_cast<double>(value * 1.0 / 12.0);
}

double operator "" _m_to_ft(long double value) {
    return static_cast<double>(value * 1.0 / 0.3048);
}

double operator "" _m_to_in(long double value) {
    return static_cast<double>(value * 1.0 / 0.0254);
}

double operator "" _m_to_cm(long double value) {
    return static_cast<double>(value * 100.0);
}

double operator "" _cm_to_m(long double value) {
    return static_cast<double>(value * 0.01);
}

double operator "" _cm_to_ft(long double value) {
    return static_cast<double>(value * 1.0 / 30.48);
}

double operator "" _cm_to_in(long double value) {
    return static_cast<double>(value * 1.0 / 30.48);

}
