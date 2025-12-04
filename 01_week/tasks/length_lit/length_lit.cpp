// Футы в другие единицы
constexpr double operator"" _ft_to_in(long double feet) {
    return static_cast<double>(feet * 12.0L);
}

constexpr double operator"" _ft_to_cm(long double feet) {
    return static_cast<double>(feet * 30.48L);
}

constexpr double operator"" _ft_to_m(long double feet) {
    return static_cast<double>(feet * 0.3048L);
}

// Дюймы в другие единицы
constexpr double operator"" _in_to_ft(long double inches) {
    return static_cast<double>(inches / 12.0L);
}

constexpr double operator"" _in_to_cm(long double inches) {
    return static_cast<double>(inches * 2.54L);
}

constexpr double operator"" _in_to_m(long double inches) {
    return static_cast<double>(inches * 0.0254L);
}

// Сантиметры в другие единицы
constexpr double operator"" _cm_to_ft(long double cm) {
    return static_cast<double>(cm / 30.48L);
}

constexpr double operator"" _cm_to_in(long double cm) {
    return static_cast<double>(cm / 2.54L);
}

constexpr double operator"" _cm_to_m(long double cm) {
    return static_cast<double>(cm / 100.0L);
}

// Метры в другие единицы
constexpr double operator"" _m_to_ft(long double meters) {
    return static_cast<double>(meters / 0.3048L);
}

constexpr double operator"" _m_to_in(long double meters) {
    return static_cast<double>(meters / 0.0254L);
}

constexpr double operator"" _m_to_cm(long double meters) {
    return static_cast<double>(meters * 100.0L);
}