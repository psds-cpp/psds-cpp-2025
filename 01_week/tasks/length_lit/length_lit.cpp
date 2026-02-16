double operator""_cm_to_m(long double x) {
    return x / 100.0;
}
double operator""_m_to_cm(long double x) {
    return x* 100.0;
}

double operator""_in_to_ft(long double x) {
    return x / 12.0;
}
double operator""_ft_to_in(long double x) {
    return x * 12.0;
}

double operator""_m_to_ft(long double x) {
    return x / 0.3048;
}
double operator""_ft_to_m(long double x) {
    return x * 0.3048;
}

double operator""_cm_to_ft(long double x) {
    return x / 30.48;
}
double operator""_ft_to_cm(long double x) {
    return x * 30.48;
}

double operator""_cm_to_in(long double x) {
    return x / 30.48 * 12.0;
}

double operator""_m_to_in(long double x) {
    return x* 100.0 / 30.48 * 12.0;
}
double operator""_in_to_cm(long double x) {
    return x / 12.0 * 30.48;
}
double operator""_in_to_m(long double x) {
    return x / 12.0 * 30.48 / 100;
}