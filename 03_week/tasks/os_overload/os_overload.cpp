#include <stdexcept>
#include <vector>
#include <utility>
#include <iostream>

struct Coord2D
{
    int x;
    int y;
};

struct Circle
{
    Coord2D coord;
    unsigned radius;

    // конструкторы
    Circle() : coord(), radius(1) {}
    Circle(Coord2D coords, unsigned r = 1) : coord(coords), radius(r) {}
};

using CircleRegion = std::pair<Circle, bool>;
using CircleRegionList = std::vector<CircleRegion>;

std::ostream& operator<<(std::ostream& os, Coord2D circle)
{
    return os << '(' << circle.x << ", " << circle.y << ')';
}

std::ostream& operator<<(std::ostream& os, Circle circle)
{
    if (!circle.radius)
        return os << "circle[]";
    return os << "circle[" << circle.coord << ", r = " << circle.radius << "]";
}

std::ostream& operator<<(std::ostream& os, CircleRegion circle)
{
    circle.second ? (os << '+') : (os << '-');
    return os << circle.first;
}

std::ostream& operator<<(std::ostream& os, CircleRegionList circle)
{
    if (circle.empty())
    {
        return os << "{}";
    }
    else
    {
        os << "{\n";
        for (size_t i = 0; i < circle.size(); ++i)
        {
            i + 1 == circle.size() ? (os << "\t" << circle[i] << "\n") : (os << "\t" << circle[i] << ",\n");
        }
        return os << '}';
    }
}