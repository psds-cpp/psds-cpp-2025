#include <stdexcept>
#include <tuple>

struct Date {
    unsigned year = 0;
    unsigned month = 0;
    unsigned day = 0;

    bool operator==(const Date& other) const {
        return std::tie(year, month, day) == std::tie(other.year, other.month, other.day);
    }
    
    bool operator!=(const Date& other) const {
        return !(*this == other);
    }

    bool operator<(const Date& other) const {
        return std::tie(year, month, day) < std::tie(other.year, other.month, other.day);
    }
    
    bool operator>(const Date& other) const {
        if (*this == other) {
            return false;
        }

        return !(*this < other);
    }

    bool operator<=(const Date& other) {
        return !(*this > other);
    }

    bool operator>=(const Date& other) {
        return !(*this < other);
    }
};

struct StudentInfo {
    size_t id;
    char mark;
    int score;
    unsigned course;
    Date birth_date;

    bool operator==(const StudentInfo& other) const {
        return mark == other.mark && score == other.score;
    }

    bool operator!=(const StudentInfo& other) const {
        return !(*this == other);
    }

    bool operator<(const StudentInfo& other) const {
        // обратный знак, так как A < Z в таблице символов
        return std::tie(other.mark, score, other.course, birth_date) < std::tie(mark, other.score, course, other.birth_date);
    }
};


