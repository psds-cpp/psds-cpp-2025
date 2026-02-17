
namespace length_const {
    constexpr double METER = 1.0;
    constexpr double CENTIMETER = 0.01;
    constexpr double FOOT = 0.3048;
    constexpr double INCH = 0.0254;
}

constexpr double operator""_ft_to_in(long double value) {
    return value * length_const::FOOT / length_const::INCH;
}
constexpr double operator""_ft_to_cm(long double value) {
    return value * length_const::FOOT / length_const::CENTIMETER;
}
constexpr double operator""_ft_to_m(long double value) {
    return value * length_const::FOOT / length_const::METER;
}
constexpr double operator""_in_to_ft(long double value) {
    return value * length_const::INCH / length_const::FOOT;
}
constexpr double operator""_in_to_cm(long double value) {
    return value * length_const::INCH / length_const::CENTIMETER;
}
constexpr double operator""_in_to_m(long double value) {
    return value * length_const::INCH / length_const::METER;
}
constexpr double operator""_cm_to_ft(long double value) {
    return value * length_const::CENTIMETER / length_const::FOOT;
}
constexpr double operator""_cm_to_in(long double value) {
    return value * length_const::CENTIMETER / length_const::INCH;
}
constexpr double operator""_cm_to_m(long double value) {
    return value * length_const::CENTIMETER / length_const::METER;
}
constexpr double operator""_m_to_ft(long double value) {
    return value * length_const::METER / length_const::FOOT;
}
constexpr double operator""_m_to_in(long double value) {
    return value * length_const::METER / length_const::INCH;
}
constexpr double operator""_m_to_cm(long double value) {
    return value * length_const::METER / length_const:: CENTIMETER;
}
