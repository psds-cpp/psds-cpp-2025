#include <stdexcept>

struct Date {
    unsigned year = 0u;
    unsigned month = 0u;
    unsigned day = 0u;

    bool operator== (const Date& other) const {
        return std::tie(year, month, day) == std::tie(other.year, other.month, other.day);
    }

    bool operator< (const Date& other) const {
        return std::tie(year, month, day) < std::tie(other.year, other.month, other.day);
    }

    bool operator!= (const Date& other) const {
        return !(*this==other);
    }

    bool operator<= (const Date& other) const {
        return (*this<other) || (*this==other);
    }

    bool operator> (const Date& other) const {
        return !(*this<=other);
    }

    bool operator>= (const Date& other) const {
        return !(*this < other);
    }
};

struct StudentInfo {
    size_t id = 0;
    char mark = 'A';
    int score = 0;
    unsigned course = 1u;
    Date birth_date{};

    bool operator== (const StudentInfo& other) const {
        return std::tie(mark, score) == std::tie(other.mark, other.score);
    }

    bool operator< (const StudentInfo& other) const {
        if (this->mark == other.mark){}
        else{
            return +this->mark > +other.mark;
        }
        if (this->score == other.score){}
        else{
            return this->score < other.score;
        }
        if (this->course == other.course){}
        else{
            return this->course > other.course;
        }
        if (this->birth_date == other.birth_date){return false;}
        else{
            return this->birth_date < other.birth_date;
        }
        
    }

};