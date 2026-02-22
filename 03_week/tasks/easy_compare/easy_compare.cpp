#include <cstddef>
#include <tuple>

struct Date {
    unsigned year = 0u;
    unsigned month = 0u;
    unsigned day = 0u;
    
    Date(){}
    Date(unsigned year, unsigned month, unsigned day) : year(year), month(month), day(day){}

    bool operator==(Date other) const {
        return std::tie(year, month, day) == std::tie(other.year, other.month, other.day);
    }

    bool operator!=(Date other) const {
        return !(*this == other);
    }

    bool operator<(Date other) const {
        return std::tie(year, month, day) < std::tie(other.year, other.month, other.day);
    }
    
    bool operator>(Date other) const {
        return std::tie(year, month, day) > std::tie(other.year, other.month, other.day);
    }

    bool operator>=(Date other) const {
        return *this > other || *this == other;
    }

    bool operator<=(Date other) const {
        return *this < other || *this == other;
    }
};

struct StudentInfo {
    size_t id;
    char mark;
    int score;
    unsigned course;
    Date birth_date;

    StudentInfo(){}
    StudentInfo(size_t id, char mark, int score, unsigned course, Date birth_date) : 
    id(id), mark(mark), score(score), course(course), birth_date(birth_date){}

    bool operator==(StudentInfo other) const {
        return std::tie(mark, score) == std::tie(other.mark, other.score);
    }

    bool operator!=(StudentInfo other) const {
        return !(*this == other);
    }

    bool operator<(StudentInfo other) const {
        return std::tie(other.mark, score, other.course, birth_date) < std::tie(mark, other.score, course, other.birth_date);
    }

    bool operator>(StudentInfo other) const {
        return std::tie(other.mark, score, other.course, birth_date) > std::tie(mark, other.score, course, other.birth_date);
    }

    bool operator>=(StudentInfo other) const {
        return *this > other || *this == other;
    }

    bool operator<=(StudentInfo other) const {
        return *this < other || *this == other;
    }
};