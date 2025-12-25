// в метрах
const double INCH = 0.0254; 
const double FOOT = 0.3048;
const double CM   = 0.01;

// перевод из дюймов в метры
double operator"" _in_to_m(long double v) {
    return v * INCH;
}
// перевод из дюймов в сантиметры
double operator"" _in_to_cm(long double v) {
    double m = v * INCH;
    return m / CM;
}
// перевод из дюймов в футы
double operator"" _in_to_ft(long double v) {
    double m = v * INCH;
    return m / FOOT;
}

// перевод из футов в метры
double operator"" _ft_to_m(long double v) {
    return v * FOOT;
}
// перевод из футов в сантиметры
double operator"" _ft_to_cm(long double v) {
    double m = v * FOOT;
    return m / CM;
}
// перевод из футов в дюймы
double operator"" _ft_to_in(long double v) {
    double m = v * FOOT;
    return m / INCH;
}

// перевод из сантиметров в метры
double operator"" _cm_to_m(long double v) {
    return v * CM;
}
// перевод из сантиметров в дюймы
double operator"" _cm_to_in(long double v) {
    double m = v * CM;
    return m / INCH;
}
// перевод из сантиметров в футы
double operator"" _cm_to_ft(long double v) {
    double m = v * CM;
    return m / FOOT;
}

// перевод из метров в сантиметры
double operator"" _m_to_cm(long double v) {
    return v / CM;
}
// перевод из метров в дюймы
double operator"" _m_to_in(long double v) {
    return v / INCH;
}
// перевод из метров в футы
double operator"" _m_to_ft(long double v) {
    return v / FOOT;
}
