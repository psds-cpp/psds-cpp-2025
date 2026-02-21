#include <stdexcept>


struct Date {
    unsigned year = 0u;
    unsigned month = 0u;
    unsigned day = 0u;
};

bool operator==(const Date& leftDate, const Date& rightDate) {
    return std::tie(leftDate.year, leftDate.month, leftDate.day) == std::tie(rightDate.year, rightDate.month, rightDate.day);
}

bool operator!=(const Date& leftDate, const Date& rightDate) {
    return !(leftDate == rightDate);
}

bool operator<(const Date& leftDate, const Date& rightDate) {
    return std::tie(leftDate.year, leftDate.month, leftDate.day) < std::tie(rightDate.year, rightDate.month, rightDate.day);
}

bool operator>(const Date& leftDate, const Date& rightDate) {
    return rightDate < leftDate;
}

bool operator<=(const Date& leftDate, const Date& rightDate) {
    return leftDate < rightDate || leftDate == rightDate;
}

bool operator>=(const Date& leftDate, const Date& rightDate) {
    return leftDate > rightDate || leftDate == rightDate;
}

struct StudentInfo {
    size_t id;
    char mark;
    int score;
    unsigned course;
    Date birth_date;
};

bool operator==(const StudentInfo& leftStudent, const StudentInfo& rightStudent) {
    return std::tie(leftStudent.mark, leftStudent.score) == std::tie(rightStudent.mark, rightStudent.score);
}

bool operator!=(const StudentInfo& leftStudent, const StudentInfo& rightStudent) {
    return !(leftStudent == rightStudent);
}

bool operator<(const StudentInfo& leftStudent, const StudentInfo& rightStudent) {
    return std::tie(
        rightStudent.mark, leftStudent.score, rightStudent.course, leftStudent.birth_date)
        < std::tie( leftStudent.mark, rightStudent.score, leftStudent.course, rightStudent.birth_date );
}

bool operator>(const StudentInfo& leftStudent, const StudentInfo& rightStudent) {
    return rightStudent < leftStudent;
}

bool operator<=(const StudentInfo& leftStudent, const StudentInfo& rightStudent) {
    return leftStudent < rightStudent || leftStudent == rightStudent;
}

bool operator>=(const StudentInfo& leftStudent, const StudentInfo& rightStudent) {
    return leftStudent > rightStudent || leftStudent == rightStudent;
}