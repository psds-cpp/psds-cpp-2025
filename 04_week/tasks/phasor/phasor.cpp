#include <cmath>
#include <iostream>
#include <stdexcept>
#include <numbers>  

struct ExpTag {};
struct DegTag {};
struct AlgTag {};

class Phasor {
private:
    double real_;  // действительная часть
    double imag_;  // мнимая часть

    // Вспомогательная функция для нормализации фазы в диапазон (-pi, pi]
    static double normalize_phase(double phase) {
        const double two_pi = 2.0 * std::numbers::pi;
        
        // Приводим фазу в диапазон [0, 2pi)
        phase = std::fmod(phase, two_pi);
        if (phase < 0) {
            phase += two_pi;
        }
        
        // Приводим фазу в диапазон (-pi, pi]
        if (phase > std::numbers::pi) {
            phase -= two_pi;
        }
        
        return phase;
    }

public:
    // Конструкторы
    // Конструктор по умолчанию - нулевой фазор
    Phasor() : real_(0.0), imag_(0.0) {}
    
    // Конструктор из полярных координат
    Phasor(double magnitude, double phase_rad) {
        if (magnitude < 0) {
            magnitude = -magnitude;
            phase_rad += std::numbers::pi;
        }
        phase_rad = normalize_phase(phase_rad);
        real_ = magnitude * std::cos(phase_rad);
        imag_ = magnitude * std::sin(phase_rad);
    }
    
    // Конструктор ExpTag 
    Phasor(double magnitude, double phase_rad, [[maybe_unused]] ExpTag tag)
        : Phasor(magnitude, phase_rad) {}
    
    // Конструктор DegTag 
    Phasor(double magnitude, double phase_deg, [[maybe_unused]] DegTag tag)
        : Phasor(magnitude, phase_deg * std::numbers::pi / 180.0) {}
    
    // Конструктор AlgTag 
    Phasor(double real, double imag, [[maybe_unused]] AlgTag tag)
        : real_(real), imag_(imag) {}
    
    // Методы доступа
    double Magnitude() const {
        return std::sqrt(real_ * real_ + imag_ * imag_);
    }
    
    double Phase() const {
        if (real_ == 0.0 && imag_ == 0.0) {
            return 0.0;
        }
        return std::atan2(imag_, real_);
    }
    
    double PhaseDeg() const {
        return Phase() * 180.0 / std::numbers::pi;
    }
    
    double Real() const {
        return real_;
    }
    
    double Imag() const {
        return imag_;
    }
    
    // Синонимы
    
    double Abs() const { return Magnitude(); }
    double Angle() const { return Phase(); }
    double AngleDeg() const { return PhaseDeg(); }
    
    // Методы модификации
    
    void SetPolar(double magnitude, double phase_rad) {
        *this = Phasor(magnitude, phase_rad);
    }
    
    void SetCartesian(double real, double imag) {
        real_ = real;
        imag_ = imag;
    }
    
    // Арифметические операторы с присваиванием
    
    Phasor& operator += (const Phasor& other) {
        real_ += other.real_;
        imag_ += other.imag_;
        return *this;
    }
    
    Phasor& operator -= (const Phasor& other) {
        real_ -= other.real_;
        imag_ -= other.imag_;
        return *this;
    }
    
    Phasor& operator *= (const Phasor& other) {
        double mag = Magnitude() * other.Magnitude();
        double phase = Phase() + other.Phase();
        real_ = mag * std::cos(phase);
        imag_ = mag * std::sin(phase);
        return *this;
    }
    
    Phasor& operator /= (const Phasor& other) {
        double other_mag = other.Magnitude();
        if (other_mag == 0.0) {
            throw std::runtime_error("Division by zero in Phasor");
        }
        double mag = Magnitude() / other_mag;
        double phase = Phase() - other.Phase();
        real_ = mag * std::cos(phase);
        imag_ = mag * std::sin(phase);
        return *this;
    }
    
    // Унарный минус
    
    Phasor operator -() const {
        return Phasor(-real_, -imag_, AlgTag{});
    }
    
    // Специальные методы
    
    Phasor Conj() const {
        return Phasor(real_, -imag_, AlgTag{});
    }
    
    Phasor Inv() const {
        double mag = Magnitude();
        if (mag == 0.0) {
            throw std::runtime_error("Inverse of zero Phasor");
        }
        double new_mag = 1.0 / mag;
        double new_phase = -Phase();
        return Phasor(new_mag, new_phase);
    }
};

// Бинарные арифметические операторы

Phasor operator + (const Phasor& a, const Phasor& b) {
    Phasor result = a;
    result += b;
    return result;
}

Phasor operator - (const Phasor& a, const Phasor& b) {
    Phasor result = a;
    result -= b;
    return result;
}

Phasor operator * (const Phasor& a, const Phasor& b) {
    Phasor result = a;
    result *= b;
    return result;
}

Phasor operator / (const Phasor& a, const Phasor& b) {
    Phasor result = a;
    result /= b;
    return result;
}

// Операции с вещественными числами

Phasor operator + (const Phasor& a, double b) {
    return a + Phasor(b, 0.0, AlgTag{});
}

Phasor operator + (double a, const Phasor& b) {
    return Phasor(a, 0.0, AlgTag{}) + b;
}

Phasor operator - (const Phasor& a, double b) {
    return a - Phasor(b, 0.0, AlgTag{});
}

Phasor operator - (double a, const Phasor& b) {
    return Phasor(a, 0.0, AlgTag{}) - b;
}

Phasor operator * (const Phasor& a, double b) {
    return a * Phasor(b, 0.0, AlgTag{});
}

Phasor operator * (double a, const Phasor& b) {
    return Phasor(a, 0.0, AlgTag{}) * b;
}

Phasor operator / (const Phasor& a, double b) {
    if (b == 0.0) {
        throw std::runtime_error("Division by zero");
    }
    return a / Phasor(b, 0.0, AlgTag{});
}

Phasor operator / (double a, const Phasor& b) {
    return Phasor(a, 0.0, AlgTag{}) / b;
}

// Операторы сравнения

bool operator == (const Phasor& a, const Phasor& b) {
    const double eps = 1e-10;
    return std::abs(a.Real() - b.Real()) < eps &&
           std::abs(a.Imag() - b.Imag()) < eps;
}

bool operator != (const Phasor& a, const Phasor& b) {
    return !(a == b);
}

// Вспомогательные функции создания

Phasor MakePhasorCartesian(double real, double imag) {
    return Phasor(real, imag, AlgTag{});
}

Phasor MakePhasorPolar(double magnitude, double phase_rad) {
    return Phasor(magnitude, phase_rad);
}

Phasor MakePhasorPolarDeg(double magnitude, double phase_deg) {
    return Phasor(magnitude, phase_deg, DegTag{});
}

// Оператор вывода в поток

std::ostream& operator << (std::ostream& os, const Phasor& p) {
    double mag = p.Magnitude();
    double phase_deg = p.PhaseDeg();
    double real = p.Real();
    double imag = p.Imag();
    
    // Форматируем вывод с фиксированной точностью
    os.precision(6);
    os << std::fixed << mag << "*e(j*" << phase_deg << ") [" 
       << real << " + j*" << imag << "]";
    return os;
}