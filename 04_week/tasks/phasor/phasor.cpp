#include <cmath>
#include <iostream>
#include <numbers>

struct ExpTag {};
struct DegTag {};
struct AlgTag {};

class Phasor {
private:
    double real_;
    double imag_;

public:
    Phasor() : real_(0.0), imag_(0.0) {}

    Phasor(double magnitude, double phase_rad) {
        double mag = std::abs(magnitude);
        double phase = phase_rad;
        if (magnitude < 0) {
            phase += std::numbers::pi;
        }
        phase = NormalizePhase(phase);
        real_ = mag * std::cos(phase);
        imag_ = mag * std::sin(phase);
    }

    Phasor(double magnitude, double phase_rad, ExpTag) 
        : Phasor(magnitude, phase_rad) {}

    Phasor(double magnitude, double phase_deg, DegTag) 
        : Phasor(magnitude, phase_deg * std::numbers::pi / 180.0) {}

    Phasor(double real, double imag, AlgTag) 
        : real_(real), imag_(imag) {
        double mag = Magnitude();
        double phase = Phase();
        real_ = mag * std::cos(phase);
        imag_ = mag * std::sin(phase);
    }
    double Magnitude() const { return std::sqrt(real_ * real_ + imag_ * imag_); }
    double Phase() const { return std::atan2(imag_, real_); }
    double PhaseDeg() const { return Phase() * 180.0 / std::numbers::pi; }
    double Real() const { return real_; }
    double Imag() const { return imag_; }

    double Abs() const { return Magnitude(); }
    double Angle() const { return Phase(); }
    double AngleDeg() const { return PhaseDeg(); }

    void SetPolar(double magnitude, double phase_rad) {
        double mag = std::abs(magnitude);
        double phase = phase_rad;
        if (magnitude < 0) {
            phase += std::numbers::pi;
        }
        phase = NormalizePhase(phase);
        real_ = mag * std::cos(phase);
        imag_ = mag * std::sin(phase);
    }

    void SetCartesian(double real, double imag) {
        real_ = real;
        imag_ = imag;
    }

    Phasor operator+() const { return *this; }
    Phasor operator-() const { return Phasor(-real_, -imag_, AlgTag{}); }

    Phasor& operator+=(const Phasor& other) {
        real_ += other.real_;
        imag_ += other.imag_;
        return *this;
    }

    Phasor& operator-=(const Phasor& other) {
        real_ -= other.real_;
        imag_ -= other.imag_;
        return *this;
    }

    Phasor& operator*=(const Phasor& other) {
        double mag = Magnitude() * other.Magnitude();
        double phase = Phase() + other.Phase();
        phase = NormalizePhase(phase);
        real_ = mag * std::cos(phase);
        imag_ = mag * std::sin(phase);
        return *this;
    }

    Phasor& operator/=(const Phasor& other) {
        double mag = Magnitude() / other.Magnitude();
        double phase = Phase() - other.Phase();
        phase = NormalizePhase(phase);
        real_ = mag * std::cos(phase);
        imag_ = mag * std::sin(phase);
        return *this;
    }

    Phasor& operator+=(double scalar) {
        real_ += scalar;
        return *this;
    }

    Phasor& operator-=(double scalar) {
        real_ -= scalar;
        return *this;
    }

    Phasor& operator*=(double scalar) {
        if (scalar < 0) {
            double mag = Magnitude() * std::abs(scalar);
            double phase = Phase() + std::numbers::pi;
            phase = NormalizePhase(phase);
            real_ = mag * std::cos(phase);
            imag_ = mag * std::sin(phase);
        } else {
            real_ *= scalar;
            imag_ *= scalar;
        }
        return *this;
    }

    Phasor& operator/=(double scalar) {

        if (scalar < 0) {
            double mag = Magnitude() / std::abs(scalar);
            double phase = Phase() + std::numbers::pi;
            phase = NormalizePhase(phase);
            real_ = mag * std::cos(phase);
            imag_ = mag * std::sin(phase);
        } else {
            real_ /= scalar;
            imag_ /= scalar;
        }
        return *this;
    }

    Phasor Conj() const { return Phasor(real_, -imag_, AlgTag{}); }
    
    Phasor Inv() const {
        double mag = Magnitude();
        if (mag == 0.0) {
            // ќбратный к нулевому фазору не определен, вернем нуль
            return Phasor();
        }
        double phase = -Phase();
        return Phasor(1.0 / mag, phase);
    }

    bool operator==(const Phasor& other) const {
        constexpr double EPS = 1e-10;
        return std::abs(real_ - other.real_) < EPS &&
               std::abs(imag_ - other.imag_) < EPS;
    }

    bool operator!=(const Phasor& other) const {
        return !(*this == other);
    }

private:
    static double NormalizePhase(double phase) {
        // ѕриводим фазу к диапазону (-?, ?]
        phase = std::fmod(phase, 2 * std::numbers::pi);
        if (phase > std::numbers::pi) {
            phase -= 2 * std::numbers::pi;
        } else if (phase <= -std::numbers::pi) {
            phase += 2 * std::numbers::pi;
        }
        return phase;
    }
};

Phasor operator+(const Phasor& lhs, const Phasor& rhs) {
    Phasor result = lhs;
    result += rhs;
    return result;
}

Phasor operator-(const Phasor& lhs, const Phasor& rhs) {
    Phasor result = lhs;
    result -= rhs;
    return result;
}

Phasor operator*(const Phasor& lhs, const Phasor& rhs) {
    Phasor result = lhs;
    result *= rhs;
    return result;
}

Phasor operator/(const Phasor& lhs, const Phasor& rhs) {
    Phasor result = lhs;
    result /= rhs;
    return result;
}

Phasor operator+(const Phasor& phasor, double scalar) {
    Phasor result = phasor;
    result += scalar;
    return result;
}

Phasor operator+(double scalar, const Phasor& phasor) {
    return phasor + scalar;
}

Phasor operator-(const Phasor& phasor, double scalar) {
    Phasor result = phasor;
    result -= scalar;
    return result;
}

Phasor operator-(double scalar, const Phasor& phasor) {
    return Phasor(scalar, 0.0, AlgTag{}) - phasor;
}

Phasor operator*(const Phasor& phasor, double scalar) {
    Phasor result = phasor;
    result *= scalar;
    return result;
}

Phasor operator*(double scalar, const Phasor& phasor) {
    return phasor * scalar;
}

Phasor operator/(const Phasor& phasor, double scalar) {
    Phasor result = phasor;
    result /= scalar;
    return result;
}

Phasor operator/(double scalar, const Phasor& phasor) {
    return Phasor(scalar, 0.0, AlgTag{}) / phasor;
}

Phasor MakePhasorCartesian(double real, double imag) {
    return Phasor(real, imag, AlgTag{});
}

Phasor MakePhasorPolar(double magnitude, double phase_rad) {
    return Phasor(magnitude, phase_rad);
}

Phasor MakePhasorPolarDeg(double magnitude, double phase_deg) {
    return Phasor(magnitude, phase_deg, DegTag{});
}

std::ostream& operator<<(std::ostream& os, const Phasor& phasor) {
    // ”станавливаем фиксированный формат с 3 знаками после зап€той
    os.precision(3);
    os << std::fixed;
    
    double mag = phasor.Magnitude();
    double arg_deg = phasor.PhaseDeg();
    double real = phasor.Real();
    double imag = phasor.Imag();
    
    os << mag << "*e(j*" << arg_deg << ") [" 
       << real << " + j*" << imag << "]";
    
    return os;
}