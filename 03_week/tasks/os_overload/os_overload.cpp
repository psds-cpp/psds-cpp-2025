#include <ostream>
#include <stdexcept>
#include <vector>
#include <utility>


struct Coord2D {
    int x {0};
    int y {0};
};

struct Circle {
    Coord2D coord {};
    unsigned radius {1};
};

using CircleRegion = std::pair<Circle, bool>;
using CircleRegionList = std::vector<CircleRegion>;

std::ostream& operator<<(std::ostream& os, const Coord2D& coord) { 
    os << std::dec << "(" << coord.x << ", " << coord.y << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Circle& circle) { 
    os << "circle" << "[";
    if (circle.radius == 0) {
        os << "]";
        return os;
    }
    os << circle.coord;
    os << ", r = " << std::dec << circle.radius;
    os << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const CircleRegion& circle_region) { 
    if (circle_region.second) {
            // внутренняя область
            os << "+";
        } else {
            // внешняя область
            os << "-";
        }
    os << circle_region.first;
    return os;
}

std::ostream& operator<<(std::ostream& os, const CircleRegionList& list) {
    if (list.empty()) {
        os << "{}";
        return os;
    }

    os << "{\n\t";
    for (const auto& circle_region : list) {
        os << circle_region;
        if (&circle_region != &list.back()) {
            os << ",\n\t";
        }
    }
    os << "\n}";

    return os;
}
