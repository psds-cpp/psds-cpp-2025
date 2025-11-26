constexpr double operator""_ft_to_m(long double feet) {
    return feet * 0.3048;
}

constexpr double operator""_in_to_m(long double inches) {
    return inches * 0.0254;
}

constexpr double operator""_cm_to_m(long double centimeters) {
    return centimeters * 0.01;
}

constexpr double operator""_m_to_ft(long double meters) {
    return meters / 0.3048;
}

constexpr double operator""_m_to_in(long double meters) {
    return meters / 0.0254;
}

constexpr double operator""_m_to_cm(long double meters) {
    return meters / 0.01;
}

constexpr double operator""_ft_to_cm(long double feet) {
    return operator""_m_to_cm(operator""_ft_to_m(feet));
}

constexpr double operator""_ft_to_in(long double feet) {
    return operator""_m_to_in(operator""_ft_to_m(feet));
}

constexpr double operator""_in_to_ft(long double inches) {
    return operator""_m_to_ft(operator""_in_to_m(inches));
}

constexpr double operator""_in_to_cm(long double inches) {
    return operator""_m_to_cm(operator""_in_to_m(inches));
}

constexpr double operator""_cm_to_ft(long double centimeters) {
    return operator""_m_to_ft(operator""_cm_to_m(centimeters));
}

constexpr double operator""_cm_to_in(long double centimeters) {
    return operator""_m_to_in(operator""_cm_to_m(centimeters));
}