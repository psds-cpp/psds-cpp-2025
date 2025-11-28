#include <cmath>

constexpr double operator "" _ft_to_m(long double value) {
    return static_cast<double>(value * 0.3048);
}

constexpr double operator "" _ft_to_cm(long double value) {
    return static_cast<double>(value * 30.48);
}

constexpr double operator "" _ft_to_in(long double value) {
    return static_cast<double>(value * 12.0);
}

constexpr double operator "" _in_to_m(long double value) {
    return static_cast<double>(value * 0.0254);
}

constexpr double operator "" _in_to_cm(long double value) {
    return static_cast<double>(value * 2.54);
}

constexpr double operator "" _in_to_ft(long double value) {
    return static_cast<double>(value / 12.0);
}

constexpr double operator "" _m_to_ft(long double value) {
    return static_cast<double>(value / 0.3048);
}

constexpr double operator "" _m_to_in(long double value) {
    return static_cast<double>(value / 0.0254);
}

constexpr double operator "" _m_to_cm(long double value) {
    return static_cast<double>(value * 100.0);
}

constexpr double operator "" _cm_to_m(long double value) {
    return static_cast<double>(value * 0.01);
}

constexpr double operator "" _cm_to_ft(long double value) {
    return static_cast<double>(value / 30.48);
}

constexpr double operator "" _cm_to_in(long double value) {
    return static_cast<double>(value / 2.54);

}



