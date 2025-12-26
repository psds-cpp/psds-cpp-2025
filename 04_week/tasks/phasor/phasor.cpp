#include <bits/stdc++.h>
#include <iomanip>

struct ExpTag {};
struct DegTag {};
struct AlgTag {};


class Phasor {
public:
    // Конструкторы (объявления)
    Phasor();
    Phasor(double amplitude, double phase);
    Phasor(double amplitude, double phase, ExpTag);
    Phasor(double amplitude, double phase, DegTag);
    Phasor(double real, double imag, AlgTag);

    // Методы (объявления)
    void SetPolar(double amplitude, double phase);
    void SetCartesian(double real, double imag);
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

    // Операторы (объявления)
    Phasor operator-() const;
    Phasor& operator+=(const Phasor& other);
    Phasor& operator-=(const Phasor& other);
    Phasor& operator*=(const Phasor& other);
    Phasor& operator/=(const Phasor& other);
    Phasor& operator+=(double val);
    Phasor& operator-=(double val);
    Phasor& operator*=(double val);
    Phasor& operator/=(double val);
    bool operator==(const Phasor& other) const;
    bool operator!=(const Phasor& other) const;
 

private:
    double re;
    double im;
    static constexpr double PI = 3.14159265358979323846;
};

// Арифметические операторы (объявления)
Phasor operator+(Phasor a, const Phasor& b);
Phasor operator-(Phasor a, const Phasor& b);
Phasor operator*(Phasor a, const Phasor& b);
Phasor operator/(Phasor a, const Phasor& b);

Phasor operator+(Phasor a, double b);
Phasor operator+(double a, const Phasor& b);
Phasor operator-(Phasor a, double b);
Phasor operator-(double a, const Phasor& b);
Phasor operator*(Phasor a, double b);
Phasor operator*(double a, const Phasor& b);
Phasor operator/(Phasor a, double b);
Phasor operator/(double a, const Phasor& b);

// Методы создания (объявления)
Phasor MakePhasorCartesian(double re, double im);
Phasor MakePhasorPolar(double amplitude, double phase);
Phasor MakePhasorPolarDeg(double amplitude, double phase);

// // Вывод в поток (объявление)
std::ostream& operator<<(std::ostream& os, const Phasor& p);


// Конструкторы (реализации)

Phasor::Phasor() : re(0.0), im(0.0) {}

Phasor::Phasor(double amplitude, double phase) {
    SetPolar(amplitude, phase);
}

Phasor::Phasor(double amplitude, double phase, ExpTag) : Phasor(amplitude, phase) {}

Phasor::Phasor(double amplitude, double phase, DegTag) {
    SetPolar(amplitude, phase * PI / 180.0);
}

Phasor::Phasor(double real, double imag, AlgTag) : re(real), im(imag) {}


// Методы (реализации)

void Phasor::SetPolar(double amplitude, double phase) {
    re = amplitude * std::cos(phase);
    im = amplitude * std::sin(phase);
}

void Phasor::SetCartesian(double real, double imag) {
    re = real;
    im = imag;
}

double Phasor::Magnitude() const {
    return std::hypot(re, im);
}

double Phasor::Abs() const {
    return Magnitude();
}

double Phasor::Phase() const {
    double p = std::atan2(im, re);
    return (p <= -PI + 1e-20) ? PI : p;
}

double Phasor::Angle() const {
    return Phase();
}

double Phasor::PhaseDeg() const {
    return Phase() * 180.0 / PI;
}

double Phasor::AngleDeg() const {
    return PhaseDeg();
}

double Phasor::Real() const {
    return re;
}

double Phasor::Imag() const {
    return im;
}

Phasor Phasor::Conj() const {
    return Phasor(re, -im, AlgTag());
}

Phasor Phasor::Inv() const {
    double denom = re * re + im * im;
    return Phasor(re / denom, -im / denom, AlgTag());
}


// Операторы (реализации)

Phasor Phasor::operator-() const {
    return Phasor(-re, -im, AlgTag());
}

Phasor& Phasor::operator+=(const Phasor& other) {
    re += other.re;
    im += other.im;
    return *this;
}

Phasor& Phasor::operator-=(const Phasor& other) {
    re -= other.re;
    im -= other.im;
    return *this;
}

Phasor& Phasor::operator*=(const Phasor& other) {
    double old_re = re;
    re = old_re * other.re - im * other.im;
    im = old_re * other.im + im * other.re;
    return *this;
}

Phasor& Phasor::operator/=(const Phasor& other) {
    double denom = other.re * other.re + other.im * other.im;
    double old_re = re;
    re = (old_re * other.re + im * other.im) / denom;
    im = (im * other.re - old_re * other.im) / denom;
    return *this;
}

Phasor& Phasor::operator+=(double val) {
    re += val;
    return *this;
}

Phasor& Phasor::operator-=(double val) {
    re -= val;
    return *this;
}

Phasor& Phasor::operator*=(double val) {
    re *= val;
    im *= val;
    return *this;
}

Phasor& Phasor::operator/=(double val) {
    re /= val;
    im /= val;
    return *this;
}

bool Phasor::operator==(const Phasor& other) const {
    return this->re == other.re && this->im == other.im;
}

bool Phasor::operator!=(const Phasor& other) const {
    return !(*this == other);
}


// Арифметические операторы (реализации)

Phasor operator+(Phasor a, const Phasor& b) {
    return a += b;
}

Phasor operator-(Phasor a, const Phasor& b) {
    return a -= b;
}

Phasor operator*(Phasor a, const Phasor& b) {
    return a *= b;
}

Phasor operator/(Phasor a, const Phasor& b) {
    return a /= b;
}

Phasor operator+(Phasor a, double b) {
    return a += b;
}

Phasor operator+(double a, const Phasor& b) {
    return Phasor(a, 0, AlgTag()) + b;
}

Phasor operator-(Phasor a, double b) {
    return a -= b;
}

Phasor operator-(double a, const Phasor& b) {
    return Phasor(a, 0, AlgTag()) - b;
}

Phasor operator*(Phasor a, double b) {
    return a *= b;
}

Phasor operator*(double a, const Phasor& b) {
    return Phasor(a, 0, AlgTag()) * b;
}

Phasor operator/(Phasor a, double b) {
    return a /= b;
}

Phasor operator/(double a, const Phasor& b) {
    return Phasor(a, 0, AlgTag()) / b;
}


// Методы создания (реализация)

Phasor MakePhasorCartesian(double re, double im) {
    return Phasor(re, im, AlgTag());
}

Phasor MakePhasorPolar(double amplitude, double phase) {
    return Phasor(amplitude, phase, ExpTag());
}

Phasor MakePhasorPolarDeg(double amplitude, double phase) {
    return Phasor(amplitude, phase, DegTag());
}


// Вывод в поток (реализация)

std::ostream& operator<<(std::ostream& os, const Phasor& p) {
    std::streamsize default_precision = os.precision();
    std::ios_base::fmtflags default_flags = os.flags();

    os << std::fixed << std::setprecision(3);
    os << p.Magnitude() << "*e(j*" << p.PhaseDeg() << ") [" << p.Real() << " + j*" << p.Imag() << "]";

    os.precision(default_precision);
    os.flags(default_flags);
    return os;
}