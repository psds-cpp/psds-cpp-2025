#include <cmath>
#include <iostream>
#include <iomanip>

struct ExpTag {};
struct DegTag {};
struct AlgTag {};

double areDoublesEqual(const double a, const double b, const double eps = 1e-12) {
    return std::abs(a - b) < eps;
}

class Phasor {
public:
    Phasor();
    Phasor(const double m, const double phi);
    Phasor(const double m, const double phi, const ExpTag& tag);
    Phasor(const double m, const double deg, const DegTag& tag);
    Phasor(const double x, const double y, const AlgTag& tag);
    void SetPolar(const double m, const double phi);
    void SetCartesian(const double x, const double y);
    double Magnitude() const;
    double Abs() const;
    double Phase() const;
    double Angle() const;
    double PhaseDeg() const;
    double AngleDeg() const;
    double Real() const;
    double Imag() const;
    Phasor Conj() const;
    Phasor Inv() const;
    bool operator==(const Phasor& other) const;
    bool operator!=(const Phasor& other) const;
    Phasor operator-() const;
    Phasor& operator+=(const Phasor& other);
    Phasor& operator-=(const Phasor& other);
    Phasor& operator/=(const Phasor& other);
    Phasor& operator*=(const Phasor& other);
private:
    double m_m = .0;
    double m_phi = .0;
    double m_deg_to_rad(const double deg) const;
    double m_rad_to_deg(const double deg) const;
    void m_normalize_magnitude();
    void m_normalize_phase();
    void m_normalize_phasor();
};

double Phasor::m_deg_to_rad(const double deg) const {
    return deg * M_PI / 180;
}

double Phasor::m_rad_to_deg(const double rad) const {
    return rad * 180 / M_PI;
}

void Phasor::m_normalize_magnitude() {
    if (m_m < 0) {
        m_m = std::abs(m_m);
        m_phi += (m_phi > 0) ? -M_PI : M_PI;
    }
}

void Phasor::m_normalize_phase() {
    m_phi = std::atan2(std::sin(m_phi), std::cos(m_phi));

    if (m_phi <= -M_PI) {
        m_phi = M_PI;
    }
}

void Phasor::m_normalize_phasor() {
    m_normalize_magnitude();
    m_normalize_phase();
}

void Phasor::SetCartesian(const double x, const double y) {
    m_m = sqrt(pow(x, 2) + pow(y, 2));
    m_phi = atan2(y, x);
    m_normalize_phasor();
}

Phasor::Phasor() {}
Phasor::Phasor(const double m, const double phi = 0) : m_m(m), m_phi(phi) {
    m_normalize_phasor();

}
Phasor::Phasor(const double m, const double phi, const ExpTag&) : Phasor(m, phi) {}
Phasor::Phasor(const double m, const double deg, const DegTag&) : Phasor(m, m_deg_to_rad(deg)) {}
Phasor::Phasor(const double x, const double y, const AlgTag&) {
    SetCartesian(x, y);
}

void Phasor::SetPolar(const double m, const double phi) {
    m_m = m;
    m_phi = phi;
    m_normalize_phasor();
}

double Phasor::Magnitude() const {
    return m_m;
}

double Phasor::Abs() const {
    return m_m;
}

double Phasor::Phase() const {
    return m_phi;
}

double Phasor::Angle() const {
    return m_phi;
}

double Phasor::PhaseDeg() const {
    return m_rad_to_deg(m_phi);
}

double Phasor::AngleDeg() const {
    return m_rad_to_deg(m_phi);
}

double Phasor::Real() const {
    return m_m * cos(m_phi);
}

double Phasor::Imag() const {
    return m_m * sin(m_phi);
}

Phasor Phasor::Conj() const {
    return Phasor(m_m, -m_phi);
}

Phasor Phasor::Inv() const {
    return Phasor(1 / m_m, -m_phi);
}

bool Phasor::operator==(const Phasor& other) const {
    return areDoublesEqual(m_m, other.m_m) && areDoublesEqual(m_phi, other.m_phi);
}

bool Phasor::operator!=(const Phasor& other) const {
    return !(*this == other);
}

Phasor Phasor::operator-() const {
    return Phasor(-m_m, m_phi);
}

Phasor& Phasor::operator+=(const Phasor& other) {
    SetCartesian(Real() + other.Real(), Imag() + other.Imag());
    return *this;
}

Phasor& Phasor::operator-=(const Phasor& other) {
    SetCartesian(Real() - other.Real(), Imag() - other.Imag());
    return *this;
}

Phasor& Phasor::operator*=(const Phasor& other) {
    SetPolar(m_m * other.m_m, m_phi + other.m_phi);
    return *this;
}

Phasor& Phasor::operator/=(const Phasor& other) {
    SetPolar(m_m / other.m_m, m_phi - other.m_phi);
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Phasor& phasor) {
    return (
        os << std::fixed << std::setprecision(3) << phasor.Magnitude()
        << "*e(j*" << phasor.PhaseDeg() << ") [" << phasor.Real()
        << " + j*" << phasor.Imag() << "]" << std::endl
    );
}

Phasor operator+(const Phasor& lhs, const Phasor& rhs) {
    return Phasor(lhs.Real() + rhs.Real(), lhs.Imag() + rhs.Imag(), AlgTag {});
}

Phasor operator-(const Phasor& lhs, const Phasor& rhs) {
    return Phasor(lhs.Real() - rhs.Real(), lhs.Imag() - rhs.Imag(), AlgTag {});
}

Phasor operator*(const Phasor& lhs, const Phasor& rhs) {
    return Phasor(lhs.Abs() * rhs.Abs(), lhs.Phase() + rhs.Phase());
}

Phasor operator/(const Phasor& lhs, const Phasor& rhs) {
    return Phasor(lhs.Abs() / rhs.Abs(), lhs.Phase() - rhs.Phase());
}

Phasor MakePhasorCartesian(const double x, const double y) {
    return Phasor(x, y, AlgTag {});
}

Phasor MakePhasorPolar(const double m, const double phi) {
    return Phasor(m, phi, ExpTag {});
}

Phasor MakePhasorPolarDeg(const double m, const double deg) {
    return Phasor(m, deg, DegTag {});
}