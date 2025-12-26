#include <ostream>
#include <stdexcept>
#include <vector>
#include <utility>


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

std::ostream& operator<<(std::ostream& os, const Coord2D& coord) {
    os << '(' << coord.x << ", " << coord.y << ')';
    return os;
}

std::ostream& operator<<(std::ostream& os, const Circle& circle) {
    os << "circle[";
    if (circle.radius != 0) 
        os << circle.coord << ", r = " << circle.radius;
    os << ']';
    return os;
}

std::ostream& operator<<(std::ostream& os, const CircleRegion& circle) {
    os << ((circle.second) ? '+' : '-') << circle.first;
    return os;
}

std::ostream& operator<<(std::ostream& os, const CircleRegionList& list) {
    os << '{';
    size_t len = list.size();
    for (size_t i = 0; i < len; ++i) {
        if (i == 0)
            os << "\n\t";

        os << list[i];

        if (i != len-1)
            os << ",\n\t";
        else
            os << '\n';
    }
    os << '}';
    return os;
}