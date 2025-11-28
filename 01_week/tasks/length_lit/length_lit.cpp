#include <cmath>

constexpr double FOOT_TO_METER = 0.3048;
constexpr double INCH_TO_METER = 0.0254;
constexpr double METER_TO_FOOT = 1.0 / FOOT_TO_METER;
constexpr double METER_TO_INCH = 1.0 / INCH_TO_METER;
constexpr double CM_TO_METER = 0.01;
constexpr double METER_TO_CM = 100.0;

constexpr double operator"" _ft_to_m(long double feet) {
    return static_cast<double>(feet) * FOOT_TO_METER;
}

constexpr double operator"" _ft_to_m(unsigned long long feet) {
    return static_cast<double>(feet) * FOOT_TO_METER;
}

constexpr double operator"" _ft_to_cm(long double feet) {
    return static_cast<double>(feet) * FOOT_TO_METER * METER_TO_CM;
}

constexpr double operator"" _ft_to_cm(unsigned long long feet) {
    return static_cast<double>(feet) * FOOT_TO_METER * METER_TO_CM;
}

constexpr double operator"" _ft_to_in(long double feet) {
    return static_cast<double>(feet) * 12.0;
}

constexpr double operator"" _ft_to_in(unsigned long long feet) {
    return static_cast<double>(feet) * 12.0;
}

constexpr double operator"" _in_to_m(long double inches) {
    return static_cast<double>(inches) * INCH_TO_METER;
}

constexpr double operator"" _in_to_m(unsigned long long inches) {
    return static_cast<double>(inches) * INCH_TO_METER;
}

constexpr double operator"" _in_to_cm(long double inches) {
    return static_cast<double>(inches) * INCH_TO_METER * METER_TO_CM;
}

constexpr double operator"" _in_to_cm(unsigned long long inches) {
    return static_cast<double>(inches) * INCH_TO_METER * METER_TO_CM;
}

constexpr double operator"" _in_to_ft(long double inches) {
    return static_cast<double>(inches) / 12.0;
}

constexpr double operator"" _in_to_ft(unsigned long long inches) {
    return static_cast<double>(inches) / 12.0;
}

constexpr double operator"" _m_to_ft(long double meters) {
    return static_cast<double>(meters) * METER_TO_FOOT;
}

constexpr double operator"" _m_to_ft(unsigned long long meters) {
    return static_cast<double>(meters) * METER_TO_FOOT;
}

constexpr double operator"" _m_to_in(long double meters) {
    return static_cast<double>(meters) * METER_TO_INCH;
}

constexpr double operator"" _m_to_in(unsigned long long meters) {
    return static_cast<double>(meters) * METER_TO_INCH;
}

constexpr double operator"" _m_to_cm(long double meters) {
    return static_cast<double>(meters) * METER_TO_CM;
}

constexpr double operator"" _m_to_cm(unsigned long long meters) {
    return static_cast<double>(meters) * METER_TO_CM;
}

constexpr double operator"" _cm_to_m(long double centimeters) {
    return static_cast<double>(centimeters) * CM_TO_METER;
}

constexpr double operator"" _cm_to_m(unsigned long long centimeters) {
    return static_cast<double>(centimeters) * CM_TO_METER;
}

constexpr double operator"" _cm_to_ft(long double centimeters) {
    return static_cast<double>(centimeters) * CM_TO_METER * METER_TO_FOOT;
}

constexpr double operator"" _cm_to_ft(unsigned long long centimeters) {
    return static_cast<double>(centimeters) * CM_TO_METER * METER_TO_FOOT;
}

constexpr double operator"" _cm_to_in(long double centimeters) {
    return static_cast<double>(centimeters) * CM_TO_METER * METER_TO_INCH;
}

constexpr double operator"" _cm_to_in(unsigned long long centimeters) {
    return static_cast<double>(centimeters) * CM_TO_METER * METER_TO_INCH;
}
