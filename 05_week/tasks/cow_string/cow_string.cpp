#include <cstring>
#include <string>

struct CWSTR
{
    char *str = nullptr;
    size_t size = 0;
    size_t capacity = 0;
    size_t *ref_count = nullptr;
};

class CowString
{
private:
    CWSTR cwstr;
    void swap(CowString &b) noexcept
    {
        using std::swap;
        swap(cwstr.str, b.cwstr.str);
        swap(cwstr.size, b.cwstr.size);
        swap(cwstr.capacity, b.cwstr.capacity);
        swap(cwstr.ref_count, b.cwstr.ref_count);
    }
    void copy_data()
    {
        char *t = cwstr.str;
        cwstr.str = new char[std::strlen(cwstr.str) + 1];
        std::strcpy(cwstr.str, t);
        --*cwstr.ref_count;
        if (*cwstr.ref_count == 0)
        {
            delete[] t;
            delete cwstr.ref_count;
        }
        cwstr.ref_count = new size_t;
        *cwstr.ref_count = 1;
    }
    void realloc_data(size_t size)
    {
        char *t = cwstr.str;
        cwstr.str = new char[size * 2];
        cwstr.capacity = size * 2;
        if (t)
            std::strcpy(cwstr.str, t);
        --*cwstr.ref_count;
        if (*cwstr.ref_count == 0)
        {
            delete[] t;
            delete cwstr.ref_count;
        }
        cwstr.ref_count = new size_t;
        *cwstr.ref_count = 1;
    }

public:
    static constexpr size_t npos = -1;
    // конструктор по умолчанию
    CowString()
    {
        cwstr.ref_count = new size_t;
        *cwstr.ref_count = 1;
    }
    // конструктор от С строки
    CowString(char *str_t, size_t size = npos)
    {
        if (size == npos)
            size = std::strlen(str_t);
        cwstr.ref_count = new size_t;
        *cwstr.ref_count = 2;
        cwstr.str = const_cast<char *>(str_t);
        cwstr.size = size;
        cwstr.capacity = cwstr.size;
    }
    CowString(const char *str_t, size_t size = npos)
    {
        if (size == npos)
            size = std::strlen(str_t);
        cwstr.ref_count = new size_t;
        *cwstr.ref_count = 1;
        cwstr.str = new char[size + 1];
        std::strcpy(cwstr.str, str_t);
        cwstr.str[size] = '\0';
        cwstr.size = size;
        cwstr.capacity = cwstr.size;
    }
    // конструктор от std::string
    CowString(std::string &str_t)
    {
        cwstr.ref_count = new size_t;
        *cwstr.ref_count = 1;
        cwstr.size = str_t.size();
        cwstr.capacity = cwstr.size;
        cwstr.str = new char[cwstr.capacity + 1];
        std::strcpy(cwstr.str, str_t.c_str());
    }
    CowString(std::string &&str_t)
    {
        cwstr.ref_count = new size_t;
        *cwstr.ref_count = 1;
        cwstr.size = str_t.size();
        cwstr.capacity = cwstr.size;
        cwstr.str = new char[cwstr.capacity + 1];
        std::strcpy(cwstr.str, str_t.c_str());
    }
    // конструктор от копирования
    CowString(const CowString &other)
        : cwstr{other.cwstr.str, other.cwstr.size, other.cwstr.capacity, other.cwstr.ref_count}
    {
        if (cwstr.ref_count)
            ++*cwstr.ref_count;
    }
    // конструктор перемещением
    CowString(CowString &&other) noexcept
    {
        cwstr.str = other.cwstr.str;
        cwstr.size = other.cwstr.size;
        cwstr.capacity = other.cwstr.capacity; // берём реальную ёмкость
        cwstr.ref_count = other.cwstr.ref_count;

        other.cwstr.str = nullptr;
        other.cwstr.size = 0;
        other.cwstr.capacity = 0;
        other.cwstr.ref_count = nullptr;
    }
    // деструктор
    ~CowString()
    {
        if (cwstr.ref_count)
        {
            --*cwstr.ref_count;
            if (*cwstr.ref_count == 0)
            {
                delete[] cwstr.str;
                delete cwstr.ref_count;
            }
        }
    }
    // операторы
    // оператор неявного преобразования
    operator char *()
    {
        return cwstr.str;
    }
    // оператор неравенства
    bool operator==(CowString &other)
    {
        if (this->cwstr.str == other.cwstr.str && this->cwstr.size == other.cwstr.size && this->cwstr.capacity == other.cwstr.capacity && this->cwstr.ref_count == other.cwstr.ref_count)
            return true;
        else
            return false;
    }
    bool operator!=(CowString &other)
    {
        return !(*this == other);
    }
    // оператор присваивания копированием
    CowString &operator=(const CowString &other)
    {
        if (this != &other)
        {

            char *old_str = cwstr.str;
            size_t *old_ref = cwstr.ref_count;

            // Копируем данные из other
            cwstr.str = other.cwstr.str;
            cwstr.size = other.cwstr.size;
            cwstr.capacity = other.cwstr.capacity;
            cwstr.ref_count = other.cwstr.ref_count;

            if (cwstr.ref_count)
                ++*cwstr.ref_count;
            if (old_ref)
            {
                --*old_ref;
                if (*old_ref == 0)
                {
                    delete[] old_str;
                    delete old_ref;
                }
            }
        }
        return *this;
    }
    // оператор присваивания от строки
    CowString &operator=(std::string &other)
    {
        if (cwstr.str != other.data())
        {
            if (*cwstr.ref_count != 1)
            {
                --cwstr.ref_count;
                cwstr.ref_count = new size_t;
                *cwstr.ref_count = 1;
            }
            cwstr.str = other.data();
            cwstr.capacity = other.size();
            cwstr.size = other.size();
        }
        return *this;
    }
    // оператор перемещения
    CowString &operator=(std::string &&other)
    {
        if (cwstr.str != other.data())
        {
            if (*cwstr.ref_count != 1)
            {
                --cwstr.ref_count;
                cwstr.ref_count = new size_t;
                *cwstr.ref_count = 1;
            }
            cwstr.str = other.data();
            cwstr.capacity = other.size();
            cwstr.size = other.size();
            copy_data();

            other.clear();
        }
        return *this;
    }
    // оператор присваивания перемещением
    CowString &operator=(CowString &&other) noexcept
    {
        if (this != &other)
        {
            // Освобождаем текущие ресурсы
            if (cwstr.ref_count)
            {
                --*cwstr.ref_count;
                if (*cwstr.ref_count == 0)
                {
                    delete[] cwstr.str;
                    delete cwstr.ref_count;
                }
            }

            // Перемещаем данные из other
            cwstr.str = other.cwstr.str;
            cwstr.size = other.cwstr.size;
            cwstr.capacity = other.cwstr.capacity;
            cwstr.ref_count = other.cwstr.ref_count;

            // Обнуляем other
            other.cwstr.str = nullptr;
            other.cwstr.size = 0;
            other.cwstr.capacity = 0;
            other.cwstr.ref_count = nullptr;
        }
        return *this;
    }
    const char &operator[](size_t pos) const
    {
        return cwstr.str[pos];
    }
    char &operator[](size_t pos)
    {
        if (*cwstr.ref_count != 1)
        {
            copy_data();
        }
        return cwstr.str[pos];
    }
    // методы
    size_t Size() const;
    bool Empty() const;
    char *ToCstr() const;
    size_t Find(const char *substr) const;
    size_t Find(const char x) const;
    std::string ToString();
    CowString &Append(const char *str_n);
    CowString &Append(const std::string &str_n);
    CowString Substr(size_t pos, size_t num) const;
    void Clear();
};

// методы, не меняющие исходные данные
size_t CowString::Size() const
{
    return cwstr.size;
}
bool CowString::Empty() const
{
    return cwstr.size == 0;
}
char *CowString::ToCstr() const
{
    return (cwstr.str ? cwstr.str : const_cast<char *>("")); // а так можно вообще константные литералы приводить???
}
std::string CowString::ToString()
{
    return std::string(cwstr.str, cwstr.size);
}
// методы, меняющие исходные данные
CowString &CowString::Append(const char *str_n)
{
    if (std::strlen(str_n) == 0)
        return *this;
    if (*cwstr.ref_count > 1 || cwstr.capacity < cwstr.size + std::strlen(str_n))
    {
        realloc_data(cwstr.size + std::strlen(str_n) + 1);
    }
    std::strcpy(cwstr.str + cwstr.size, str_n);
    cwstr.size += std::strlen(str_n);
    return *this;
}
CowString &CowString::Append(const std::string &str_n)
{
    if (str_n.size() == 0)
        return *this;
    if (*cwstr.ref_count > 1 || cwstr.capacity < cwstr.size + str_n.size())
    {
        realloc_data(cwstr.size + str_n.size());
    }
    std::strcpy(cwstr.str + cwstr.size, str_n.data());
    cwstr.size += str_n.size();
    return *this;
}
CowString CowString::Substr(size_t pos = 0, size_t num = npos) const
{
    if (pos <= cwstr.size && cwstr.size != 0)
    {
        if (num + pos > cwstr.size || num == npos)
        {
            num = cwstr.size - pos;
        }
        char *t = new char[num + 1];
        std::strncpy(t, cwstr.str + pos, num);
        t[num] = '\0';
        CowString result(static_cast<const char *>(t), num); // используем конструктор от константной строки, чтобы скопировать ее (не получить dangling pointer)
        delete[] t;
        return result;
    }
    else
        return "";
}
size_t CowString::Find(const char *substr) const
{
    char *t = std::strstr(cwstr.str, substr);
    return t ? t - cwstr.str : npos;
}
size_t CowString::Find(const char x) const
{
    char *t = std::strchr(cwstr.str, x);
    return t ? t - cwstr.str : npos;
}
void CowString::Clear()
{
    if (cwstr.ref_count)
    {
        if (*cwstr.ref_count > 1)
        {
            --*cwstr.ref_count;
        }
        else
        {
            delete[] cwstr.str;
            delete cwstr.ref_count;
        }
    }
    cwstr.str = nullptr;
    cwstr.size = 0;
    cwstr.capacity = 0;
    cwstr.ref_count = new size_t(1);
}