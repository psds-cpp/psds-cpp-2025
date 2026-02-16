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

std::ostream& operator<<(std::ostream& os, Coord2D& coord) {
    os << "("<< coord.x << ", "  << coord.y << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, Circle& circle) {
    os << "circle[";
    if (circle.radius != 0){
        os << circle.coord << ", r = " << circle.radius;
    } 
    os << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, CircleRegion& region) {
    if (region.second){
        os << "+";
    }
    else{
        os << "-";
    }
    if (region.first.radius != 0){
        os << region.first;
    }
    else{
        os << "circle[]";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, CircleRegionList& list) {
    size_t size_list = size(list);
    os << "{";
    if (size_list != 0){
        os << std::endl;
    }
    for (size_t i = 0; i < size_list; ++i) {
            os << '\t' << list[i];
        if (i != (size_list - 1)){
            os << ",";
        }
        os << std::endl;
    }
    os << "}";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Coord2D& coord) {
    os << "("<< coord.x << ", "  << coord.y << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Circle& circle) {
    os << "circle[";
    if (circle.radius != 0){
        os << circle.coord << ", r = " << circle.radius;
    } 
    os << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const CircleRegion& region) {
    if (region.second){
        os << "+";
    }
    else{
        os << "-";
    }
    if (region.first.radius != 0){
        os << region.first;
    }
    else{
        os << "circle[]";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const CircleRegionList& list) {
    size_t size_list = size(list);
    os << "{";
    if (size_list != 0){
        os << std::endl;
    }
    for (size_t i = 0; i < size_list; ++i) {
            os << '\t' << list[i];
        if (i != (size_list - 1)){
            os << ",";
        }
        os << std::endl;
    }
    os << "}";
    return os;
}