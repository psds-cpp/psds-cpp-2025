
// Константы для преобразования
#define IN_TO_CM 2.54
#define FT_TO_IN 12.0
#define M_TO_CM 100.0


constexpr double operator"" _ft_to_m(long double x) {
    return static_cast<double>(x / M_TO_CM * FT_TO_IN * IN_TO_CM); // преобразование фт в метры 
}

constexpr double operator"" _ft_to_cm(long double x) {
    return static_cast<double>(x * FT_TO_IN * IN_TO_CM); // преобразование фт в см 
}

constexpr double operator"" _ft_to_in(long double x) {
    return static_cast<double>( x * FT_TO_IN); // преобразование фт в дюймы 
}


//Дюймы
constexpr double operator"" _in_to_m(long double x) {
   return static_cast<double>(x * IN_TO_CM / M_TO_CM); 
}

constexpr double operator"" _in_to_cm(long double x) {
    return static_cast<double>(x * IN_TO_CM); // 
}

constexpr double operator"" _in_to_ft(long double x) {
    return static_cast<double>(x / FT_TO_IN); // 
}

//Метры
constexpr double operator"" _m_to_ft(long double x) {
   return static_cast<double>(x / IN_TO_CM / FT_TO_IN * M_TO_CM); //  
}

constexpr double operator"" _m_to_cm(long double x) {
    return static_cast<double>( x * M_TO_CM); // 
}

constexpr double operator"" _m_to_in(long double x) {
    return static_cast<double>(x / IN_TO_CM * M_TO_CM); // 
}


//см
constexpr double operator"" _cm_to_ft(long double x) {
    return static_cast<double>(x / FT_TO_IN / IN_TO_CM); //  
}

constexpr double operator"" _cm_to_m(long double x) {
     return static_cast<double>(x / M_TO_CM); // 
}

constexpr double operator"" _cm_to_in(long double x) {
    return static_cast<double>(x / IN_TO_CM); // 
}



