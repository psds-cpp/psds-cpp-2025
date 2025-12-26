// ==== Перевод футов ====
constexpr long double operator""_ft_to_m(long double ft) {
    return ft * 0.3048L;
}

constexpr long double operator""_ft_to_cm(long double ft) {
    return ft * 30.48L;
}

constexpr long double operator""_ft_to_in(long double ft) {
    return ft * 12.0L;
}

// ==== Перевод дюймов ====
constexpr long double operator""_in_to_m(long double in) {
    return in * 0.0254L;
}

constexpr long double operator""_in_to_cm(long double in) {
    return in * 2.54L;
}

constexpr long double operator""_in_to_ft(long double in) {
    return in / 12.0L;
}

// ==== Перевод метров ====
constexpr long double operator""_m_to_ft(long double m) {
    return m * 3.280839895L;
}

constexpr long double operator""_m_to_in(long double m) {
    return m * 39.37007874L;
}

constexpr long double operator""_m_to_cm(long double m) {
    return m * 100.0L;
}

// ==== Перевод сантиметров ====
constexpr long double operator""_cm_to_m(long double cm) {
    return cm / 100.0L;
}

constexpr long double operator""_cm_to_ft(long double cm) {
    return cm * 0.03280839895L;
}

constexpr long double operator""_cm_to_in(long double cm) {
    return cm * 0.3937007874L;
}