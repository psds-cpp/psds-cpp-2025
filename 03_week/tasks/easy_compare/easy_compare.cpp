#include <stdexcept>
#include <tuple>

struct Date
{
    unsigned year;
    unsigned month;
    unsigned day;
};

struct StudentInfo
{
    size_t id;
    char mark;
    int score;
    unsigned course;
    Date birth_date;
};

bool operator<(const Date &s1, const Date &s2)
{
    return std::tie(s1.year, s1.month, s1.day) < std::tie(s2.year, s2.month, s2.day);
}

bool operator==(const Date &s1, const Date &s2)
{
    return std::tie(s1.year, s1.month, s1.day) == std::tie(s2.year, s2.month, s2.day);
}

bool operator==(const StudentInfo &s1, const StudentInfo &s2)
{
    return std::tie(s1.mark, s1.score) == std::tie(s2.mark, s2.score);
}

bool operator<(const StudentInfo &s1, const StudentInfo &s2)
{
    return std::tie(s2.mark, s1.score, s2.course, s1.birth_date) <
           std::tie(s1.mark, s2.score, s1.course, s2.birth_date);
}

bool operator!=(const StudentInfo &s1, const StudentInfo &s2) { return !(s1 == s2); }
bool operator>(const StudentInfo &s1, const StudentInfo &s2) { return s2 < s1; }
bool operator<=(const StudentInfo &s1, const StudentInfo &s2) { return !(s2 < s1); }
bool operator>=(const StudentInfo &s1, const StudentInfo &s2) { return !(s1 < s2); }

bool operator!=(const Date &d1, const Date &d2) { return !(d1 == d2); }
bool operator>(const Date &d1, const Date &d2) { return d2 < d1; }
bool operator<=(const Date &d1, const Date &d2) { return !(d2 < d1); }
bool operator>=(const Date &d1, const Date &d2) { return !(d1 < d2); }
