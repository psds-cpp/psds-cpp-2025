#pragma once

constexpr long double operator"" _ft_to_m(long double x)  {return x * 0.3048L;}
constexpr long double operator"" _ft_to_cm(long double x) {return x * 30.48L;}
constexpr long double operator"" _ft_to_in(long double x) {return x * 12.0L;}

constexpr long double operator"" _in_to_m(long double x)  {return x * 0.0254L;}
constexpr long double operator"" _in_to_cm(long double x) {return x * 2.54L;}
constexpr long double operator"" _in_to_ft(long double x) {return x / 12.0L;}

constexpr long double operator"" _m_to_ft(long double x) {return x * 3.280839895L;}
constexpr long double operator"" _m_to_in(long double x) {return x * 39.37007874L;}
constexpr long double operator"" _m_to_cm(long double x) {return x * 100.0L;}

constexpr long double operator"" _cm_to_m(long double x) {return x / 100.0L;}
constexpr long double operator"" _cm_to_ft(long double x) {return x * 0.0328084L;}
constexpr long double operator"" _cm_to_in(long double x) {return x * 0.3937007874L;}