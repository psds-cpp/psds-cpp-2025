#include <ostream>
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

std::ostream& operator<<(std::ostream& os, const Circle& c) {

    if (c.radius == 0) {
        os << "circle[]";
        return os;
    }
    
    os << "circle[" << c.coord << ", " << "r = " << c.radius << ']';
    
    return os;
}

std::ostream& operator<<(std::ostream& os, const CircleRegion& r) {
    if (r.second == true) {
        os << '+';
    } else {
        os << '-';
    }
    
    os << r.first;

    return os;
}

std::ostream& operator<<(std::ostream& os, const CircleRegionList& lst) {
    if (lst.empty()) {
        os << "{}";
        return os;
    }

    os << "{";

    bool first = true;

    for (auto val : lst) {
        if (!first) {
            os << ',';
        }
        
        os << std::endl << '\t' << val;
        
        first = false;
    }

    os << std::endl <<"}";

    return os;
}
