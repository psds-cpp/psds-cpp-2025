namespace {
    constexpr double IN_IN_FT = 12.0;   //дюймов в футе
    constexpr double CM_IN_FT = 30.48;  //сантиметров в футе
    constexpr double CM_IN_M = 100;     //сантиметров в метре
    constexpr double CM_IN_IN = 2.54;   //сантиметров в дюйме
}

//Футы в дюймы
constexpr double operator""_ft_to_in(long double ft) {
    return ft * IN_IN_FT;
}

//Футы в сантиметры
constexpr double operator""_ft_to_cm(long double ft) {
    return ft * CM_IN_FT;
}

//Футы в метры
constexpr double operator""_ft_to_m(long double ft) {
    return (ft * CM_IN_FT) / CM_IN_M;
}

//Дюймы в футы
constexpr double operator""_in_to_ft(long double in) {
    return in / IN_IN_FT;
}

//Дюймы в сантиметры
constexpr double operator""_in_to_cm(long double in) {
    return in * CM_IN_IN;
}

//Дюймы в метры
constexpr double operator""_in_to_m(long double in) {
    return (in * CM_IN_IN) / CM_IN_M;
}

//Сантиметры в футы
constexpr double operator""_cm_to_ft(long double cm) {
    return cm / CM_IN_FT;
}

//Сантиметры в дюймы
constexpr double operator""_cm_to_in(long double cm) {
    return cm / CM_IN_IN;
}

//Сантиметры в метры
constexpr double operator""_cm_to_m(long double cm) {
    return cm / CM_IN_M;
}

//Метры в футы
constexpr double operator""_m_to_ft(long double m) {
    return (m * CM_IN_M) / CM_IN_FT;
}

//Метры в дюймы
constexpr double operator""_m_to_in(long double m) {
    return (m * CM_IN_M) / CM_IN_IN;
}

//Метры в сантиметры
constexpr double operator""_m_to_cm(long double m) {
    return m * CM_IN_M;
}