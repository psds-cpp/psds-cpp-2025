#include <stdexcept>
#include <vector>
#include <utility>
#include <iostream>

// struct Coord2D {
//     int x = 0;
//     int y = 0;
// };

// struct Circle {
//     Coord2D coord;
//     unsigned radius = 1;
    
//     Circle() = default;
//     Circle(const Coord2D& c) : coord(c) {}
//     Circle(const Coord2D& c, unsigned r) : coord(c), radius(r) {}
// };

// using CircleRegion = std::pair<Circle, bool>;
// using CircleRegionList = std::vector<CircleRegion>;

// std::ostream& operator<<(std::ostream& os, const Coord2D& coord) {
//     os << "(" << coord.x << ", " << coord.y << ")";
//     return os;
// }

// std::ostream& operator<<(std::ostream& os, const Circle& circle) {
//     os << "circle[";
//     if (circle.radius > 0) {
//         os << circle.coord << ", r = " << circle.radius;
//     }
//     os << "]";
//     return os;
// }

// std::ostream& operator<<(std::ostream& os, const CircleRegion& region) {
//     os << (region.second ? "+" : "-") << region.first;
//     return os;
// }

// std::ostream& operator<<(std::ostream& os, const CircleRegionList& list) {
//     if (list.empty()) {
//         os << "{}";
//     } else {
//         os << "{\n";
//         for (size_t i = 0; i < list.size(); ++i) {
//             os << "\t" << list[i];
//             if (i != list.size() - 1) {
//                 os << ",";
//             }
//             os << "\n";
//         }
//         os << "}";
//     }
//     return os;
// }

struct Coord2D
{
    int x = 0;
    int y =0;
};

struct Circle 
{
    Coord2D coord;
    unsigned radius = 1;

    Circle() = default;
    Circle(const Coord2D& c) : coord(c) {} 
    Circle(const Coord2D& c, unsigned r) : coord(c), radius(r) {} 
};

using CircleRegion = std::pair<Circle, bool>;
using CircleRegionList = std::vector<CircleRegion>;

std::ostream& operator<<(std::ostream& os, const Coord2D& coord) {
    os << '(' << coord.x << ", " << coord.y << ')';
    return os;
}

std::ostream& operator<<(std::ostream& os, const Circle& circle) {
    os << "circle[";
    if (circle.radius == 0) {
        os << ']';
        return os;
    }
    os << circle.coord << ", r = " << circle.radius << ']';
    return os;
}

std::ostream& operator<<(std::ostream& os, const CircleRegion& region) {
    if (region.second) {
        os << '+' << region.first;
    } else {
        os << '-' << region.first;
    }
    return os;
}
std::ostream& operator<<(std::ostream& os, const CircleRegionList& list) {
    if (list.empty()) {
        os << "{}";
        return os;
    }

    os << '{' << '\n';
    for (auto i = list.cbegin(); i != list.cend(); ++i) {
        os << '\t' << *i;
        if (i != list.cend() - 1) {
            os << ',';
        }
        os << '\n';
    }
    os << '}';
    return os;
}


