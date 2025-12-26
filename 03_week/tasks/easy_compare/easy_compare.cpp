#include <tuple>
#include <iostream>
#include <stddef.h>


struct Date {
    unsigned year = 0u;
    unsigned month = 0u;
    unsigned day = 0u;
};

struct StudentInfo {
    size_t id;
    char mark;
    int score;
    unsigned course;
    Date birth_date;
};

bool operator<(Date lhs, Date rhs) {
    return std::tie(lhs.year, lhs.month, lhs.day) < std::tie(rhs.year, rhs.month, rhs.day);
}

bool operator==(Date lhs, Date rhs) {
    return std::tie(lhs.year, lhs.month, lhs.day) == std::tie(rhs.year, rhs.month, rhs.day);
}

bool operator!=(Date lhs, Date rhs) {
    return !(lhs == rhs);
}

bool operator>(Date lhs, Date rhs) {
    return !(lhs < rhs || lhs == rhs);
}

bool operator>=(Date lhs, Date rhs) {
    return !(lhs < rhs);
}

bool operator<=(Date lhs, Date rhs) {
    return lhs < rhs || lhs == rhs;
}

bool operator<(StudentInfo& lhs, StudentInfo& rhs) {
    if (lhs.mark != rhs.mark) {
        return lhs.mark > rhs.mark;
    }
    else if (lhs.score != rhs.score) {
        return lhs.score < rhs.score;
    }
    else if (lhs.course != rhs.course) {
        return lhs.course > rhs.course;
    }
    else {
        return lhs.birth_date < rhs.birth_date;
    }
}

bool operator==(StudentInfo& lhs, StudentInfo& rhs) {
    return lhs.mark == rhs.mark && lhs.score == rhs.score;
}

bool operator!=(StudentInfo& lhs, StudentInfo& rhs) {
    return !(lhs == rhs);
}

bool operator>(StudentInfo& lhs, StudentInfo& rhs) {
    return !(lhs < rhs || lhs == rhs);
}

bool operator>=(StudentInfo& lhs, StudentInfo& rhs) {
    return !(lhs < rhs);
}

bool operator<=(StudentInfo& lhs, StudentInfo& rhs) {
    return lhs < rhs || lhs == rhs;
}