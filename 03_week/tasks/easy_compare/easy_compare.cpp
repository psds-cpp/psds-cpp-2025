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

bool operator<(const Date& lhs, const Date& rhs) {
    return std::tie(lhs.year, lhs.month, lhs.day) < std::tie(rhs.year, rhs.month, rhs.day);
}

bool operator==(const Date& lhs, const Date& rhs) {
    return std::tie(lhs.year, lhs.month, lhs.day) == std::tie(rhs.year, rhs.month, rhs.day);
}

bool operator!=(const Date& lhs, const Date& rhs) {
    return !(lhs == rhs);
}

bool operator>(const Date& lhs, const Date& rhs) {
    return !(lhs < rhs || lhs == rhs);
}

bool operator>=(const Date& lhs, const Date& rhs) {
    return !(lhs < rhs);
}

bool operator<=(const Date& lhs, const Date& rhs) {
    return lhs < rhs || lhs == rhs;
}

bool operator<(const StudentInfo& lhs, const StudentInfo& rhs) {
    return (
        std::tie(rhs.mark, lhs.score, rhs.course, lhs.birth_date)
        < std::tie(lhs.mark, rhs.score, lhs.course, rhs.birth_date)
    );
}

bool operator==(const StudentInfo& lhs, const StudentInfo& rhs) {
    return lhs.mark == rhs.mark && lhs.score == rhs.score;
}

bool operator!=(const StudentInfo& lhs, const StudentInfo& rhs) {
    return !(lhs == rhs);
}

bool operator>(const StudentInfo& lhs, const StudentInfo& rhs) {
    return !(lhs < rhs || lhs == rhs);
}

bool operator>=(const StudentInfo& lhs, const StudentInfo& rhs) {
    return !(lhs < rhs);
}

bool operator<=(const StudentInfo& lhs, const StudentInfo& rhs) {
    return lhs < rhs || lhs == rhs;
}