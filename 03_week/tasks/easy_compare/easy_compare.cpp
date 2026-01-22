#include <stdexcept>
#include <tuple>

struct Date {
    unsigned year;
    unsigned month;
    unsigned day;
    
    Date() : year(0), month(0), day(0) {}
    
     Date(unsigned y, unsigned m, unsigned d) : year(y), month(m), day(d) {}
};

struct StudentInfo {
    size_t id;
    char mark;
    int score;
    unsigned course;
    Date birth_date;
};

bool operator==(const Date& lhs, const Date& rhs) {
    return std::tie(lhs.year, lhs.month, lhs.day) == 
           std::tie(rhs.year, rhs.month, rhs.day);
}

bool operator!=(const Date& lhs, const Date& rhs) {
    return !(lhs == rhs);
}

bool operator<(const Date& lhs, const Date& rhs) {
    return std::tie(lhs.year, lhs.month, lhs.day) < 
           std::tie(rhs.year, rhs.month, rhs.day);
}

bool operator<=(const Date& lhs, const Date& rhs) {
    return !(rhs < lhs);
}

bool operator>(const Date& lhs, const Date& rhs) {
    return rhs < lhs;
}

bool operator>=(const Date& lhs, const Date& rhs) {
    return !(lhs < rhs);
}

int mark_priority(char mark) {
    switch (mark) {
        case 'A': return 5;
        case 'B': return 4;
        case 'C': return 3;
        case 'D': return 2;
        case 'Z': return 1;
        default: return 0;
    }
}

bool operator==(const StudentInfo& lhs, const StudentInfo& rhs) {
    return lhs.mark == rhs.mark && lhs.score == rhs.score;
}

bool operator!=(const StudentInfo& lhs, const StudentInfo& rhs) {
    return !(lhs == rhs);
}

bool operator<(const StudentInfo& lhs, const StudentInfo& rhs) {
    int lhs_priority = mark_priority(lhs.mark);
    int rhs_priority = mark_priority(rhs.mark);
    
    if (lhs_priority != rhs_priority) {
        return lhs_priority < rhs_priority;
    }

    if (lhs.score != rhs.score) {
        return lhs.score < rhs.score;
    }
    
    if (lhs.course != rhs.course) {
        return lhs.course > rhs.course;
    }
    
    return lhs.birth_date < rhs.birth_date;
}