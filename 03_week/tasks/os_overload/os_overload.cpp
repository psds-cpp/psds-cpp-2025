#include <iostream>
#include <stdexcept>
#include <vector>
#include <utility>

struct Coord2D {
    int x = 0;
    int y = 0;

    Coord2D() = default;
    Coord2D(int x_val, int y_val) : x(x_val), y(y_val) {}
};

struct Circle {
    Coord2D coord = {0, 0};
    unsigned radius = 1;

    Circle() = default;
    Circle(Coord2D c, unsigned r = 1) : coord(c), radius(r) {}
};

using CircleRegion = std::pair<Circle, bool>;
using CircleRegionList = std::vector<CircleRegion>;

std::ostream& operator<<(std::ostream& os, const Coord2D& coord) {
    os << "(" << coord.x << ", " << coord.y << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Circle& circle) {
    if (circle.radius == 0) {
        os << "circle[]";
    } else {
        os << "circle[" << circle.coord << ", r = " << circle.radius << "]";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const CircleRegion& region) {
    os << (region.second ? "+" : "-") << region.first;
    return os;
}

std::ostream& operator<<(std::ostream& os, const CircleRegionList& list) {
    if (list.empty()) {
        os << "{}";
    } else {
        os << "{\n";
        for (size_t i = 0; i < list.size(); ++i) {
            os << "\t" << list[i];
            if (i < list.size() - 1) {
                os << ",";
            }
            os << "\n";
        }
        os << "}";
    }
    return os;
}