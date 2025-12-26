constexpr long double operator""_m_to_in(long double m) {
    return m / 0.0254;
}

constexpr long double operator""_m_to_ft(long double m) {
    return m / 0.3048;
}

constexpr long double operator""_m_to_m(long double m) {
    return m;
}

constexpr long double operator""_m_to_cm(long double m) {
    return m * 100;
}

// foots
constexpr long double operator""_ft_to_in(long double ft) {
    return ft * (0.3048 / 0.0254);
}

constexpr long double operator""_ft_to_ft(long double ft) {
    return ft;
}

constexpr long double operator""_ft_to_m(long double ft) {
    return ft * 0.3048;
}

constexpr long double operator""_ft_to_cm(long double ft) {
    return ft * 30.48;
}


// inch
constexpr long double operator""_in_to_in(long double in) {
    return in;
}

constexpr long double operator""_in_to_ft(long double in) {
    return in * (0.0254 / 0.3048);
}

constexpr long double operator""_in_to_m(long double in) {
    return in * 0.0254;
}

constexpr long double operator""_in_to_cm(long double in) {
    return in * 2.54;
}


// cm
constexpr long double operator""_cm_to_in(long double cm) {
    return cm / 2.54;
}

constexpr long double operator""_cm_to_ft(long double cm) {
    return cm / 30.48;
}

constexpr long double operator""_cm_to_m(long double cm) {
    return cm / 100;
}

constexpr long double operator""_cm_to_cm(long double cm) {
    return cm;
}
