#include <cstddef>
#include <compare>

struct Date {
    unsigned year {};
    unsigned month {};
    unsigned day {};

    auto operator<=>(const Date&) const noexcept = default;
};

struct StudentInfo {
    size_t id;
    char mark;
    int score;
    unsigned course;
    Date birth_date;

    bool operator==(const StudentInfo& other) const noexcept {
        return mark == other.mark && score == other.score;
    }

    auto operator<(const StudentInfo& other) const noexcept {
        if (mark != other.mark) 
            return other.mark < mark; // обратный порядок
        if (score != other.score) 
            return score < other.score;
        if (course != other.course) 
            return other.course < course; // обратный порядок
        if (birth_date != other.birth_date) 
            return birth_date < other.birth_date; 
        
        return false;
    }
};