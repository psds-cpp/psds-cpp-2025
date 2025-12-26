#include <cmath>
#include <iostream>
#include <iomanip>

struct ExpTag {};
struct DegTag {};
struct AlgTag {};

class Phasor {
private:
    double re_;
    double im_;
public:
    Phasor() : re_(0.0), im_(0.0) {}
    Phasor(double mag, double phase_rad) { SetPolar(mag, phase_rad); }
    Phasor(double mag, double phase_rad, ExpTag) : Phasor(mag, phase_rad) {}
    Phasor(double mag, double phase_deg, DegTag) {
        double rad = phase_deg * M_PI / 180.0;
        SetPolar(mag, rad);}
    Phasor(double real, double imag, AlgTag) : re_(real), im_(imag) {}
    void SetPolar(double mag, double phase_rad) {
        re_ = mag * std::cos(phase_rad);
        im_ = mag * std::sin(phase_rad);}
    void SetCartesian(double real, double imag) { re_ = real; im_ = imag; }
    double Magnitude() const { return std::hypot(re_, im_); }
    double Phase() const {
        double angle = std::atan2(im_, re_);
        return angle; }
    double PhaseDeg() const {
        double deg = Phase() * 180.0 / M_PI;
        if (deg <= -180.0) deg += 360.0;
        else if (deg > 180.0) deg -= 360.0;
        return deg;}
    double Real() const { return re_; }
    double Imag() const { return im_; }
    double Abs() const { return Magnitude(); }
    double Angle() const { return Phase(); }
    double AngleDeg() const { return PhaseDeg(); }
    Phasor Conj() const { return Phasor(re_, -im_, AlgTag()); }
    Phasor Inv() const {
        double mag2 = re_*re_ + im_*im_;
        return Phasor(re_/mag2, -im_/mag2, AlgTag());}
    Phasor& operator+=(const Phasor& rhs) { re_+=rhs.re_; im_+=rhs.im_; return *this; }
    Phasor& operator-=(const Phasor& rhs) { re_-=rhs.re_; im_-=rhs.im_; return *this; }
    Phasor& operator*=(const Phasor& rhs) {
        double old_re = re_;
        re_ = old_re*rhs.re_ - im_*rhs.im_;
        im_ = old_re*rhs.im_ + im_*rhs.re_;
        return *this;}
    Phasor& operator/=(const Phasor& rhs) {
        double denom = rhs.re_*rhs.re_ + rhs.im_*rhs.im_;
        double old_re = re_;
        re_ = (old_re*rhs.re_ + im_*rhs.im_) / denom;
        im_ = (im_*rhs.re_ - old_re*rhs.im_) / denom;
        return *this;}
    Phasor& operator+=(double rhs) { re_+=rhs; return *this; }
    Phasor& operator-=(double rhs) { re_-=rhs; return *this; }
    Phasor& operator*=(double rhs) { re_*=rhs; im_*=rhs; return *this; }
    Phasor& operator/=(double rhs) { re_/=rhs; im_/=rhs; return *this; }
    Phasor operator-() const { return Phasor(-re_, -im_, AlgTag()); }
};
inline Phasor operator+(Phasor lhs, const Phasor& rhs){ return lhs+=rhs; }
inline Phasor operator-(Phasor lhs, const Phasor& rhs){ return lhs-=rhs; }
inline Phasor operator*(Phasor lhs, const Phasor& rhs){ return lhs*=rhs; }
inline Phasor operator/(Phasor lhs, const Phasor& rhs){ return lhs/=rhs; }
inline Phasor operator+(Phasor lhs, double rhs){ return lhs+=rhs; }
inline Phasor operator+(double lhs, const Phasor& rhs){ return Phasor(lhs,0,AlgTag())+rhs; }
inline Phasor operator-(Phasor lhs, double rhs){ return lhs-=rhs; }
inline Phasor operator-(double lhs, const Phasor& rhs){ return Phasor(lhs,0,AlgTag())-rhs; }
inline Phasor operator*(Phasor lhs, double rhs){ return lhs*=rhs; }
inline Phasor operator*(double lhs, const Phasor& rhs){ return Phasor(lhs,0,AlgTag())*rhs; }
inline Phasor operator/(Phasor lhs, double rhs){ return lhs/=rhs; }
inline Phasor operator/(double lhs, const Phasor& rhs){ return Phasor(lhs,0,AlgTag())/rhs; }
inline bool operator==(const Phasor& lhs,const Phasor& rhs){ return lhs.Real()==rhs.Real() && lhs.Imag()==rhs.Imag(); }
inline bool operator!=(const Phasor& lhs,const Phasor& rhs){ return !(lhs==rhs); }
inline Phasor MakePhasorCartesian(double r,double i){ return Phasor(r,i,AlgTag()); }
inline Phasor MakePhasorPolar(double m,double p){ return Phasor(m,p,ExpTag()); }
inline Phasor MakePhasorPolarDeg(double m,double d){ return Phasor(m,d,DegTag()); }
inline std::ostream& operator<<(std::ostream& os,const Phasor& p){
    os << std::fixed << std::setprecision(3)
       << p.Magnitude() << "*e(j*" << p.PhaseDeg() << ") ["
       << p.Real() << " + j*" << p.Imag() << "]";
    return os;
}
