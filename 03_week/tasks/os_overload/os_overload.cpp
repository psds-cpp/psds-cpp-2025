#include <iostream>
#include <vector>

struct Coord2D {
    int x = 0;
    int y = 0;
    Coord2D() = default;
    Coord2D(int x_, int y_) : x(x_), y(y_) {}};
std::ostream& operator<<(std::ostream& os, const Coord2D& coord) {
    os << "(" << coord.x << ", " << coord.y << ")";
    return os;}
struct Circle {
    Coord2D coord;
    unsigned int radius = 1;
    Circle() = default;
    Circle(const Coord2D& c, unsigned int r = 1) : coord(c), radius(r) {}
    bool isEmpty() const { return radius == 0; }};
std::ostream& operator<<(std::ostream& os, const Circle& c) {
    if (c.isEmpty()) {
        os << "circle[]";} 
        else {
        os << "circle[" << c.coord << ", r = " << c.radius << "]";}
    return os;}
struct CircleRegion {
    Circle circle;
    bool flag = true; // true = '+', false = '-'
    CircleRegion(const Circle& c, bool f) : circle(c), flag(f) {}
    CircleRegion(const std::pair<Circle,bool>& p) : circle(p.first), flag(p.second) {}};
std::ostream& operator<<(std::ostream& os, const CircleRegion& region) {
    os << (region.flag ? "+" : "-") << region.circle;
    return os;}
using CircleRegionList = std::vector<CircleRegion>;
std::ostream& operator<<(std::ostream& os, const CircleRegionList& list) {
    if (list.empty()) {
        os << "{}";
        return os;}
    os << "{\n";
    for (size_t i = 0; i < list.size(); ++i) {
        os << "\t" << list[i];
        if (i + 1 != list.size()) os << ",";
        os << "\n";}
    os << "}";
    return os;
}
