namespace {
    constexpr long double INCHES_PER_FOOT = 12.0L;
    constexpr long double CM_PER_INCH = 2.54L;
    constexpr long double M_PER_FOOT = 0.3048L;
    constexpr long double CM_PER_FOOT = M_PER_FOOT * 100.0L;
    constexpr long double M_PER_INCH = CM_PER_INCH / 100.0L;
    constexpr long double CM_PER_METER = 100.0L;
}

// ==== Перевод футов ====
constexpr long double operator""_ft_to_m(long double ft) {
    return ft * M_PER_FOOT;
}

constexpr long double operator""_ft_to_cm(long double ft) {
    return ft * CM_PER_FOOT;
}

constexpr long double operator""_ft_to_in(long double ft) {
    return ft * INCHES_PER_FOOT;
}

// ==== Перевод дюймов ====
constexpr long double operator""_in_to_m(long double in) {
    return in * M_PER_INCH;
}

constexpr long double operator""_in_to_cm(long double in) {
    return in * CM_PER_INCH;
}

constexpr long double operator""_in_to_ft(long double in) {
    return in / INCHES_PER_FOOT;
}

// ==== Перевод метров ====
constexpr long double operator""_m_to_ft(long double m) {
    return m / M_PER_FOOT;
}

constexpr long double operator""_m_to_in(long double m) {
    return m / M_PER_INCH;
}

constexpr long double operator""_m_to_cm(long double m) {
    return m * CM_PER_METER;
}

// ==== Перевод сантиметров ====
constexpr long double operator""_cm_to_m(long double cm) {
    return cm / CM_PER_METER;
}

constexpr long double operator""_cm_to_ft(long double cm) {
    return cm / CM_PER_FOOT;
}

constexpr long double operator""_cm_to_in(long double cm) {
    return cm / CM_PER_INCH;
}