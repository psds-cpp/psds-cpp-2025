#include <cstddef>
#include <cstring>
#include <string>

class CowString {
public:
    static inline constexpr size_t npos = static_cast<size_t>(-1);
    // Конструктры (объявления)
    CowString();
    CowString(const char* str);
    CowString(std::string str);
    CowString(const CowString& other);
    CowString& operator=(const CowString &other);
    CowString(CowString&& other) noexcept;
    CowString& operator=(CowString&& other) noexcept;
    ~CowString();

    // Методы (объявления, без копирования)
    size_t Size() const;
    const char* ToCstr() const;
    std::string ToString() const;
    const char& operator[](size_t index) const;
    operator const char*() const;
    bool Empty() const;
    size_t Find(const char* str) const;
    size_t Find(char ch) const;

    // Методы (объявления, с копированием)
    char& operator[](size_t index);
    CowString& Append(const char* str);
    CowString& Append(const std::string& str);
    CowString Substr(size_t start = 0, size_t len = npos);
    void Clear();
    
private:
    char* data;
    int* ref_count;

    void release();
    void detach();
};

void CowString::release() {
    if (ref_count) {
        --(*ref_count);
        if (*ref_count == 0) {
            delete[] data;
            delete ref_count;
        }
    }
}

void CowString::detach() {
    if (ref_count && *ref_count > 1) {
        size_t len = strlen(data);
        char* new_data = new char[len + 1];
        memcpy(new_data, data, len + 1);
        
        --(*ref_count); 
        data = new_data;
        ref_count = new int(1); 
    }
}

// Конструкторы (реализации)
CowString::CowString() {
    data = new char[1];
    data[0] = '\0';
    ref_count = new int(1);
}

CowString::CowString(const char* str) {
    size_t len = strlen(str);
    data = new char[len + 1];
    memcpy(data, str, len + 1);
    ref_count = new int(1);
}

CowString::CowString(std::string str) {
    size_t len = str.length();
    data = new char[len + 1];
    memcpy(data, str.c_str(), len + 1);
    ref_count = new int(1);
}

CowString::CowString(const CowString& other) : data(other.data), ref_count(other.ref_count) {
    if (ref_count) {
        ++(*ref_count);
    }
}

CowString& CowString::operator=(const CowString& other) {
    if (this != &other) {
        release();
        data = other.data;
        ref_count = other.ref_count;
        if (ref_count) {
            ++(*ref_count);
        }
    }
    return *this;
}

CowString::CowString(CowString&& other) noexcept : data(other.data), ref_count(other.ref_count) {
    other.data = new char[1]{'\0'};
    other.ref_count = new int(1);
}

CowString& CowString::operator=(CowString&& other) noexcept {
    if (this != &other) {
        release();
        data = other.data;
        ref_count = other.ref_count;
        other.data = new char[1]{'\0'};;
        other.ref_count = new int(1);
    }
    return *this;
}

CowString::~CowString() {
    release();
}

// Методы (реализации, без копирования)
size_t CowString::Size() const {
    return (data) ? strlen(data) : 0;
}

const char* CowString::ToCstr() const {
    return data;
}

std::string CowString::ToString() const {
    return std::string((data) ? data : "");
}

const char& CowString::operator[](size_t index) const {
    return data[index];
}

CowString::operator const char*() const {
    return data;
}

bool CowString::Empty() const {
    return (!data || data[0] == '\0');
}

size_t CowString::Find(const char* str) const {
    if (!str || !data) {
        return npos;
    }
    if (*str == '\0') {
        return 0;
    }
    const char* found = strstr(data, str);
    if (found) {
        return static_cast<size_t>(found - data);
    }
    return npos;
}

size_t CowString::Find(char ch) const {
    if (!data) {
        return npos;
    }
    const char* found = strchr(data, ch);
    if (found) {
        return static_cast<size_t>(found - data);
    }
    return npos;
}

// Методы (реализации, с копированием)
char& CowString::operator[](size_t index) {
    detach();
    return data[index];
}

CowString& CowString::Append(const char* str) {
    if (!str || *str == '\0') {
        return *this;
    }
    
    size_t old_len = Size();
    size_t add_len = strlen(str);
    char* new_data = new char[old_len + add_len + 1];
    
    memcpy(new_data, data, old_len);
    memcpy(new_data + old_len, str, add_len + 1);
    
    release(); 
    data = new_data;
    ref_count = new int(1);
    return *this;
}

CowString& CowString::Append(const std::string& str) {
    return Append(str.c_str());
}

CowString CowString::Substr(size_t start, size_t len) {
    size_t cur_len = Size();
    if (start >= cur_len) {
        return CowString();
    }
    
    if (len > cur_len - start) {
        len = cur_len - start;
    }
    
    char* sub = new char[len + 1];
    memcpy(sub, data + start, len);
    sub[len] = '\0';
    
    CowString res(sub);
    delete[] sub;
    return res;
}

void CowString::Clear() {
    release();
    data = new char[1];
    data[0] = '\0';
    ref_count = new int(1);
}