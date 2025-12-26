#include <stdexcept>


struct Date {
    unsigned year;
    unsigned month;
    unsigned day;

    Date (unsigned y = 0u, unsigned m = 0u, unsigned d = 0u) : year(y), month(m), day(d) {}
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
    if (leftStudent.mark != rightStudent.mark)
        return leftStudent.mark > rightStudent.mark;
    if (leftStudent.score != rightStudent.score)
        return leftStudent.score < rightStudent.score;
    if (leftStudent.course != rightStudent.course)
        return leftStudent.course > rightStudent.course;
    if (leftStudent.birth_date != rightStudent.birth_date)
        return leftStudent.birth_date < rightStudent.birth_date;
    return false;
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