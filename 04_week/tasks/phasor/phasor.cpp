#include <cmath>
#include <iomanip>
#include <ios>
#include <ostream>

namespace {
    constexpr double EPS_ = 1e-12;
}


double DegToRad(double deg) {
    return deg * M_PI / 180.0;
}

double RadToDeg(double rad){
    return rad * 180 / M_PI;
}

double NormalizePhase(double phase) {
    phase = std::fmod(phase, 2.0 * M_PI);

    if (phase > M_PI) {
        phase -= 2.0 * M_PI;
    }

    if (phase <= -M_PI) {
        phase += 2.0 * M_PI;
    }

    return phase;
}

struct ExpTag {};
struct DegTag {};
struct AlgTag {};


class Phasor {
public:
    Phasor() = default;
    Phasor(double A, double rad) {
        if (A < 0) {
            A = -A;
            rad += M_PI;
        }

        rad = NormalizePhase(rad);

        real_ = A * std::cos(rad);
        imag_ = A * std::sin(rad);
    };
    Phasor(double A, double rad, ExpTag) : Phasor(A, rad) {};
    Phasor(double A, double deg, DegTag) : Phasor(A, DegToRad(deg)) {};
    Phasor(double real, double imag, AlgTag) : real_(real), imag_(imag) {};

    void SetPolar(double A, double rad);
    void SetCartesian(double real, double imag);
    double Magnitude() const;
    double Phase() const;
    double PhaseDeg() const;
    double Real() const;
    double Imag() const;
    double Abs() const;
    double Angle() const;
    double AngleDeg() const;
    Phasor Conj() const;
    Phasor Inv() const;

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
        SetPolar(Magnitude() * other.Magnitude(), Phase() + other.Phase());
        return *this; 
    }
        
    Phasor& operator/=(const Phasor& other) {
        SetPolar(Magnitude() / other.Magnitude(), Phase() - other.Phase());
        return *this; 
    }

    Phasor& operator+=(double real) {
        real_ += real;
        return *this;
    }
    
    Phasor& operator-=(double real) {
        real_ -= real;
        return *this;
    }

    Phasor& operator*=(double real) {
        real_ *= real;
        imag_ *= real;
        return *this; 
    }
    
    Phasor& operator/=(double real) {
        real_ /= real;
        imag_ /= real;
        return *this; 
    }    
                
    Phasor operator-() const {
        return Phasor(-real_, -imag_, AlgTag{});
    }
    
private:
    double real_ = 0.0;
    double imag_ = 0.0;
};

Phasor operator+(const Phasor& lhs, const Phasor& rhs) {
    double real = lhs.Real() + rhs.Real();
    double imag = lhs.Imag() + rhs.Imag();
    return Phasor(real, imag, AlgTag{});
}

Phasor operator-(const Phasor& lhs, const Phasor& rhs) {
    double real = lhs.Real() - rhs.Real();
    double imag = lhs.Imag() - rhs.Imag();
    return Phasor(real, imag, AlgTag{});
}

Phasor operator*(const Phasor& lhs, const Phasor& rhs) {
    double A = lhs.Magnitude() * rhs.Magnitude();
    double rad = lhs.Phase() + rhs.Phase();

    return Phasor(A, NormalizePhase(rad));
}

Phasor operator/(const Phasor& lhs, const Phasor& rhs) {
    double A = lhs.Magnitude() / rhs.Magnitude();
    double rad = lhs.Phase() - rhs.Phase();

    return Phasor(A, NormalizePhase(rad));    
}

bool operator==(const Phasor& lhs, const Phasor& rhs) {
    return (std::abs(lhs.Real() - rhs.Real()) < EPS_ &&
            std::abs(lhs.Imag() - rhs.Imag()) < EPS_);
}

bool operator!=(const Phasor& lhs, const Phasor& rhs) {
    return !(lhs == rhs);
}

Phasor operator+(const Phasor& lhs, double rhs) {
    return Phasor(lhs.Real() + rhs, lhs.Imag(), AlgTag{});
}

// Сложение коммутативно
Phasor operator+(double rhs, const Phasor& lhs) {
    return Phasor(lhs.Real() + rhs, lhs.Imag(), AlgTag{});
}
    
Phasor operator-(const Phasor& lhs, double rhs) {
    return Phasor(lhs.Real() - rhs, lhs.Imag(), AlgTag{});
}

Phasor operator-(double lhs, const Phasor& rhs) {
    return (lhs + (-rhs));
}


Phasor operator*(const Phasor& lhs, double rhs) {
    return Phasor(lhs.Real() * rhs, lhs.Imag() * rhs, AlgTag{});
}

// Умножение тоже коммутативно
Phasor operator*(double rhs, const Phasor& lhs) {
    return Phasor(lhs.Real() * rhs, lhs.Imag() * rhs, AlgTag{});
}
    
Phasor operator/(const Phasor& lhs, double rhs) {
    return Phasor(lhs.Real() / rhs, lhs.Imag() / rhs, AlgTag{});
}
        
Phasor operator/(double lhs, const Phasor& rhs) {
    double A = std::abs(lhs) / rhs.Magnitude();
    double rad = ((lhs >= 0) ? 0.0 : M_PI) - rhs.Phase();
    return Phasor(A, NormalizePhase(rad));
}

std::ostream& operator<<(std::ostream& os, const Phasor& p) {
    os << std::fixed << std::setprecision(3)
       << p.Magnitude() << "*e(j*" << p.PhaseDeg() << ") ["
       << p.Real() << " + j*" << p.Imag() << ']';
    return os;
}

void Phasor::SetPolar(double A, double rad) {
    *this = Phasor(A, rad);
}

void Phasor::SetCartesian(double real, double imag) {
    real_ = real;
    imag_ = imag;
}

double Phasor::Magnitude() const {
    return std::hypot(real_, imag_);
}

double Phasor::Phase() const {
    return std::atan2(imag_, real_);
}

double Phasor::PhaseDeg() const {
    return RadToDeg(Phase());
}

double Phasor::Real() const {
    return real_;
}

double Phasor::Imag() const {
    return imag_;
}

double Phasor::Abs() const {
    return Magnitude();
}

double Phasor::Angle() const {
    return Phase();
}

double Phasor::AngleDeg() const {
    return PhaseDeg();
}

Phasor Phasor::Conj() const {
    return Phasor(real_, -imag_, AlgTag{});
}

Phasor Phasor::Inv() const {
    return 1.0 / (*this);
}

Phasor MakePhasorCartesian(double real, double imag) {
    return Phasor(real, imag, AlgTag{});
}

Phasor MakePhasorPolar(double A, double rad) {
    return Phasor(A, rad);
}

Phasor MakePhasorPolarDeg(double A, double deg) {
    return Phasor(A, deg, DegTag{});
}
