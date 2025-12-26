#include <vector>
#include <utility>
#include <iostream>


struct Coord2D {
    int x = 0;
    int y = 0;
};

struct Circle {
    Coord2D coord{};
    unsigned radius = 1;
};

using CircleRegion = std::pair<Circle, bool>;
using CircleRegionList = std::vector<CircleRegion>;

std::ostream& operator<<(std::ostream& lhs, const Coord2D& rhs) {
    return lhs << '(' << rhs.x << ", " << rhs.y << ')';
}

std::ostream& operator<<(std::ostream& lhs, const Circle& rhs) {
    if (rhs.radius == 0) {
        return lhs << "circle[]";
    }

    return lhs << "circle[" << rhs.coord << ", r = " << rhs.radius << "]";
}

std::ostream& operator<<(std::ostream& lhs, const CircleRegion& rhs) {
    return lhs << (rhs.second ? '+' : '-') << rhs.first;
}

std::ostream& operator<<(std::ostream& lhs, const CircleRegionList& rhs) {
    lhs << "{";

    if (!rhs.empty()) {
        lhs << "\n";
        lhs << '\t' << rhs[0];
    }

    for (size_t i = 1; i < rhs.size(); ++i) {
        lhs << ",\n\t" << rhs[i];
    }

    lhs << (rhs.empty() ? "}" : "\n}");

    return lhs;
}
