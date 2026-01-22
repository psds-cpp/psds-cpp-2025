#include <stdexcept>
#include <vector>
#include <utility>
#include <iostream>


struct Coord2D {
    int x=0;
    int y=0;

    Coord2D() = default;;
    Coord2D(int x_in, int y_in): x(x_in), y(y_in){};
};

struct Circle {
    Coord2D coord{};
    unsigned radius = 1u;

    Circle() = default;
    Circle(Coord2D c, unsigned r=1u): coord(c), radius(r){};
};

using CircleRegion = std::pair<Circle, bool>;
using CircleRegionList = std::vector<CircleRegion>;

std::ostream& operator << (std::ostream& os, const Coord2D& coordination){
    os << "(" << coordination.x << ", " << coordination.y << ")";
    return os;
}

std::ostream& operator << (std::ostream& os, Circle circle){
    os << "circle[";
    if (circle.radius == 0u) {
        os <<"]";
    }
    else {
        os << circle.coord << ", r = " << circle.radius << "]";
    }
    return os;
}

std::ostream& operator << (std::ostream& os, CircleRegion circRegion){
    circRegion.second ? os << "+" : os << "-";
    os << circRegion.first;
    return os;
}

std::ostream& operator << (std::ostream& os, CircleRegionList circRegionVector){
    os << "{";

    for (auto circRegion = circRegionVector.begin(); circRegion != circRegionVector.end(); ++circRegion){
        if (circRegion == circRegionVector.begin()) os << "\n";
        os << "\t" <<  *circRegion;
        if (circRegion != circRegionVector.end() - 1) os << ",";
        os << "\n";
    }
    os << "}";
    return os;
}
