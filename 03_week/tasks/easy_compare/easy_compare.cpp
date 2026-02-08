#include <tuple>

struct Date {
    unsigned year = 0;
    unsigned month = 0;
    unsigned day = 0;
};

struct StudentInfo {
    size_t id = 0;
    char mark = 'Z';
    int score = 0;
    unsigned course = 0;
    Date birth_date;
};


bool operator<(const Date& lhs, const Date& rhs){
    return std::tie(lhs.year, lhs.month, lhs.day) < std::tie(rhs.year, rhs.month, rhs.day);
}

bool operator==(const Date& lhs, const Date& rhs){
    return std::tie(lhs.year, lhs.month, lhs.day) == std::tie(rhs.year, rhs.month, rhs.day);
}

bool operator<=(const Date& lhs, const Date& rhs){
    return lhs < rhs || lhs == rhs;
}

bool operator>(const Date& lhs, const Date& rhs){
    return rhs <= lhs;
}

bool operator>=(const Date& lhs, const Date& rhs){
    return lhs > rhs || lhs == rhs;;
}

bool operator<(const StudentInfo& lhs, const StudentInfo& rhs){
    return std::tie(rhs.mark, lhs.score, rhs.course, lhs.birth_date) < std::tie(lhs.mark, rhs.score, lhs.course, rhs.birth_date);
}

bool operator==(const StudentInfo& lhs, const StudentInfo& rhs){
    return std::tie(lhs.mark, lhs. score) == std::tie(rhs.mark, rhs. score);
}

bool operator<=(const StudentInfo& lhs, const StudentInfo& rhs){
    return lhs < rhs || lhs == rhs;
}

bool operator>(const StudentInfo& lhs, const StudentInfo& rhs){
    return rhs <= lhs;
}