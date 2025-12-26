#include <cmath>
#include <ostream>
#include <iomanip>
#include <stdexcept>

struct ExpTag {};
struct DegTag {};
struct AlgTag {};

class Phasor {
public:
    Phasor() : r_(0.0), i_(0.0) {}

    Phasor(double mag, double phase) { SetPolar(mag, phase); }

    Phasor(double mag, double phase, ExpTag) : Phasor(mag, phase) {}

    Phasor(double mag, double phase_deg, DegTag) {
        SetPolar(mag, phase_deg * kDegToRad);
    }

    Phasor(double r, double i, AlgTag) : r_(r), i_(i) {}

    void SetPolar(double mag, double phase) {
        if (mag < 0.0) {
            mag = -mag;
            phase += M_PI;
        }
        r_ = mag * std::cos(phase);
        i_ = mag * std::sin(phase);
    }

    void SetCartesian(double r, double i) {
        r_ = r;
        i_ = i;
    }

    double Magnitude() const { return std::hypot(r_, i_); }
    double Abs() const { return Magnitude(); }

    double Phase() const {
        return NormalizeRad(std::atan2(i_, r_));
    }

    double PhaseDeg() const {
        return NormalizeDeg(Phase() * kRadToDeg);
    }

    double Angle() const { return Phase(); }
    double AngleDeg() const { return PhaseDeg(); }

    double Real() const { return r_; }
    double Imag() const { return i_; }

    Phasor Conj() const { return Phasor(r_, -i_, AlgTag{}); }

    Phasor Inv() const {
        double d = r_ * r_ + i_ * i_;
        if (d == 0.0)
            throw std::runtime_error("division by zero");
        return Phasor(r_ / d, -i_ / d, AlgTag{});
    }

    Phasor& operator+=(const Phasor& p) {
        r_ += p.r_;
        i_ += p.i_;
        return *this;
    }

    Phasor& operator-=(const Phasor& p) {
        r_ -= p.r_;
        i_ -= p.i_;
        return *this;
    }

    Phasor& operator*=(const Phasor& p) {
        SetPolar(Magnitude() * p.Magnitude(), Phase() + p.Phase());
        return *this;
    }

    Phasor& operator/=(const Phasor& p) {
        SetPolar(Magnitude() / p.Magnitude(), Phase() - p.Phase());
        return *this;
    }

    Phasor& operator*=(double x) {
        r_ *= x;
        i_ *= x;
        return *this;
    }

    Phasor& operator/=(double x) {
        r_ /= x;
        i_ /= x;
        return *this;
    }

    Phasor operator-() const { return Phasor(-r_, -i_, AlgTag{}); }

    bool operator==(const Phasor& p) const {
        constexpr double eps = 1e-9;
        return std::abs(r_ - p.r_) < eps &&
               std::abs(i_ - p.i_) < eps;
    }

    bool operator!=(const Phasor& p) const { return !(*this == p); }

private:
    double r_, i_;

    static constexpr double kRadToDeg = 180.0 / M_PI;
    static constexpr double kDegToRad = M_PI / 180.0;

    static double NormalizeRad(double x) {
        while (x <= -M_PI) x += 2 * M_PI;
        while (x >  M_PI)  x -= 2 * M_PI;
        return x;
    }

    static double NormalizeDeg(double x) {
        while (x <= -180.0) x += 360.0;
        while (x >  180.0)  x -= 360.0;
        return x;
    }
};

inline Phasor operator+(Phasor a, const Phasor& b) { return a += b; }
inline Phasor operator-(Phasor a, const Phasor& b) { return a -= b; }
inline Phasor operator*(Phasor a, const Phasor& b) { return a *= b; }
inline Phasor operator/(Phasor a, const Phasor& b) { return a /= b; }

inline Phasor operator+(const Phasor& p, double x) { return p + Phasor(x, 0, AlgTag{}); }
inline Phasor operator+(double x, const Phasor& p) { return Phasor(x, 0, AlgTag{}) + p; }

inline Phasor operator-(const Phasor& p, double x) { return p - Phasor(x, 0, AlgTag{}); }
inline Phasor operator-(double x, const Phasor& p) { return Phasor(x, 0, AlgTag{}) - p; }

inline Phasor operator*(Phasor p, double x) { return p *= x; }
inline Phasor operator*(double x, Phasor p) { return p *= x; }

inline Phasor operator/(Phasor p, double x) { return p /= x; }
inline Phasor operator/(double x, const Phasor& p) { return Phasor(x, 0, AlgTag{}) / p; }

inline Phasor MakePhasorCartesian(double r, double i) {
    return Phasor(r, i, AlgTag{});
}

inline Phasor MakePhasorPolar(double m, double a) {
    return Phasor(m, a);
}

inline Phasor MakePhasorPolarDeg(double m, double a) {
    return Phasor(m, a, DegTag{});
}

inline std::ostream& operator<<(std::ostream& os, const Phasor& p) {
    std::ios old(nullptr);
    old.copyfmt(os);

    os << std::fixed << std::setprecision(3)
       << p.Magnitude()
       << "*e(j*" << p.PhaseDeg() << ") "
       << "[" << p.Real() << " + j*" << p.Imag() << "]";

    os.copyfmt(old);
    return os;
}

