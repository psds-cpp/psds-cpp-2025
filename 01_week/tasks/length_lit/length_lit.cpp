#pragma once

constexpr double ft_to_m = 0.3048;
constexpr double ft_to_cm = 30.48;
constexpr double ft_to_in = 12.0;

constexpr double operator"" _ft_to_m(long double x)  {return x * ft_to_m;}
constexpr double operator"" _ft_to_cm(long double x) {return x * ft_to_cm;}
constexpr double operator"" _ft_to_in(long double x) {return x * ft_to_in;}

constexpr double in_to_m = 0.0254;
constexpr double in_to_cm = 2.54;
constexpr double in_to_ft = 12.0;

constexpr double operator"" _in_to_m(long double x)  {return x * in_to_m;}
constexpr double operator"" _in_to_cm(long double x) {return x * in_to_cm;}
constexpr double operator"" _in_to_ft(long double x) {return x / in_to_ft;}

constexpr double m_to_ft = 3.280839895;
constexpr double m_to_in = 39.37007874;
constexpr double m_to_cm = 100.0;

constexpr double operator"" _m_to_ft(long double x) {return x * m_to_ft;}
constexpr double operator"" _m_to_in(long double x) {return x * m_to_in;}
constexpr double operator"" _m_to_cm(long double x) {return x * m_to_cm;}

constexpr double cm_to_m = 100.0;
constexpr double cm_to_ft = 0.0328084;
constexpr double cm_to_in = 0.3937007874;

constexpr double operator"" _cm_to_m(long double x) {return x / cm_to_m;}
constexpr double operator"" _cm_to_ft(long double x) {return x * cm_to_ft;}
constexpr double operator"" _cm_to_in(long double x) {return x * cm_to_in;}