#include <stdexcept>
#include <vector>
#include <utility>
#include <iostream>


struct Coord2D {
    int x;
    int y;
    Coord2D(int x_val = 0, int y_val = 0) : x(x_val), y(y_val) {}
};

struct Circle {
    Coord2D coord;
    unsigned radius = 1;
    Circle() : coord(), radius(1) {}    // Default
    explicit Circle(Coord2D c, unsigned r = 1) : coord(c), radius(r) {}
    Circle(unsigned r) : coord(), radius(r) {}
};

using CircleRegion = std::pair<Circle, bool>;
using CircleRegionList = std::vector<CircleRegion>;

// Оператор вывода для Coord2D
std::ostream& operator<<(std::ostream& os, const Coord2D& coord) {
    os << '(' << coord.x << ", " << coord.y << ')';
    return os;
}

// Оператор вывода для Circle
std::ostream& operator<<(std::ostream& os, const Circle& circle) {
    os << "circle[";
    if (circle.radius > 0) {
        os << circle.coord << ", r = " << circle.radius;
    }
    os << ']';
    return os;
}

// Оператор вывода для CircleRegion
std::ostream& operator<<(std::ostream& os, const CircleRegion& region) {
    os << (region.second ? '+' : '-') << region.first;
    return os;
}

std::ostream& operator<<(std::ostream& os, const CircleRegionList& circle_vector) {
    os << '{';
    if (!circle_vector.empty()) {
        os << '\n';
        for (auto it = circle_vector.begin(); it != circle_vector.end(); ++it) {
            os << '\t' << *it;
            if (std::next(it) != circle_vector.end()) {
                os << ',';
            }
            os << '\n';
        }
    }
    os << '}';
    return os;
}
