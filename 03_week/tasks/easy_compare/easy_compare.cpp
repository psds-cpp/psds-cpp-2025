#include <stdexcept>


struct Date {
    unsigned year = 0;
    unsigned month = 0;
    unsigned day = 0;
};

struct StudentInfo {
    size_t id;
    char mark;
    int score;
    unsigned course;
    Date birth_date;
};

bool operator==(const Date& date1, const Date& date2) {
    return std::tie(date1.year, date1.month, date1.day) == std::tie(date2.year, date2.month, date2.day);
}
bool operator<(const Date& date1, const Date& date2) {
    return std::tie(date1.year, date1.month, date1.day) < std::tie(date2.year, date2.month, date2.day);
}
bool operator!=(const Date& date1, const Date& date2) {
    return !(date1 == date2);
}
bool operator>(const Date& date1, const Date& date2) {
    return !(date1 < date2 || date1 == date2);
}
bool operator>=(const Date& date1, const Date& date2) {
    return !(date1 < date2);
}
bool operator<=(const Date& date1, const Date& date2) {
    return (date1 < date2 || date1 == date2);
}

bool operator==(const StudentInfo& student1, const StudentInfo& student2) {
    return std::tie(student1.mark, student1.score) == std::tie(student2.mark, student2.score);
}
bool operator<(const StudentInfo& student1, const StudentInfo& student2) {
    if (student1.mark != student2.mark) return student1.mark > student2.mark;
    if (student1.score != student2.score) return student1.score < student2.score;
    if (student1.course != student2.course) return student1.course > student2.course;
    if (student1.birth_date != student2.birth_date) return student1.birth_date < student2.birth_date;
    return false;
}
