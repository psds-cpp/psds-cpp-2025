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
//
bool operator < (const Date& lhs, const Date& rhs){
   return std::tie(lhs.year, lhs.month, lhs.day) < std::tie(rhs.year, rhs.month, rhs.day);
}
bool operator == (const Date& lhs, const Date& rhs){
   return std::tie(lhs.year, lhs.month, lhs.day) == std::tie(rhs.year, rhs.month, rhs.day);
}
bool operator!=(const Date& lhs, const Date& rhs) {
    return !(lhs == rhs);
}

bool operator<=(const Date& lhs, const Date& rhs) {
    return (lhs < rhs) || (lhs == rhs);
}

bool operator>(const Date& lhs, const Date& rhs) {
    return !(lhs <= rhs);  
}

bool operator>=(const Date& lhs, const Date& rhs) {
    return !(lhs < rhs);  
}
//
bool operator == (const StudentInfo& lhs, const StudentInfo& rhs){
    return std::tie(lhs.mark, lhs.score) == std::tie(rhs.mark, rhs.score);
}

bool operator<(const StudentInfo& lhs, const StudentInfo& rhs) {
    if (lhs.mark != rhs.mark) {
        return rhs.mark < lhs.mark;  
    }
    
    if (lhs.score != rhs.score) {
        return rhs.score > lhs.score; 
    }
    
    if (lhs.course != rhs.course) {
        return lhs.course > rhs.course;
    }
    
    return lhs.birth_date < rhs.birth_date;
}
bool operator!=(const StudentInfo& lhs, const StudentInfo& rhs) {
    return !(lhs == rhs);
}

bool operator<=(const StudentInfo& lhs, const StudentInfo& rhs) {
    return (lhs < rhs) || (lhs == rhs);
}

bool operator>(const StudentInfo& lhs, const StudentInfo& rhs) {
    return !(lhs <= rhs);
}

bool operator>=(const StudentInfo& lhs, const StudentInfo& rhs) {
    return !(lhs < rhs);
}