#include <stdexcept>
#include <vector>
#include <utility>
#include <iostream>

struct Coord2D {
    int x = 0;
    int y = 0;
};

struct Circle {
    Coord2D coord;
    unsigned radius = 1;
};

using CircleRegion = std::pair<Circle, bool>;
using CircleRegionList = std::vector<CircleRegion>;


std::ostream& operator<<(std::ostream& os, const Coord2D& coord2D) {
    os << "("<< coord2D.x << ", " << coord2D.y << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Circle& circle) {
    if (circle.radius == 0) {
        os << "circle[]";
        return os;
    }
    os << "circle["<< circle.coord << ", r = " << circle.radius << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const CircleRegion& circleRegion) {
    os << (circleRegion.second ? "+" : "-");
    os << circleRegion.first;
    return os;
}

std::ostream& operator<<(std::ostream& os, const CircleRegionList& circleRegionList) {
    if (circleRegionList.empty()) {
        os << "{}";
        return os;
    }
    os << "{" << "\n";
    for (size_t i = 0; i < circleRegionList.size() - 1; ++i) {
        os << "\t" << circleRegionList[i] << "," << "\n";
    }
    os << "\t" << circleRegionList[circleRegionList.size() - 1] << "\n" << "}";
    return os;
}
