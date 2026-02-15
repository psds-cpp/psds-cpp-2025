#include <cstring>
#include <string>

class CowString {
private:
    struct Data {
        char* str;
        int ref_count;

        Data(const char* s) : ref_count(1) {
            str = new char[strlen(s) + 1];
            strcpy(str, s);
        }

        ~Data() {
            delete[] str;
        }

        void AddRef() {
            ++ref_count;
        }

        void Release() {
            if (--ref_count == 0) {
                delete this;
            }
        }
        
        bool IsShared() const {
            return ref_count > 1;
        }
    };

    Data* data_;
    
public:
    static const size_t npos;

    // Конструкторы
    CowString();
    CowString(const char* s);
    CowString(const std::string& s);
    CowString(const CowString& cs);
    CowString(CowString&& other) noexcept;

    // Операторы присваивания
    CowString& operator=(const CowString& other);
    CowString& operator=(CowString&& other) noexcept;

    // Деструктор
    ~CowString();

    // Методы доступа
    size_t Size() const;
    const char* ToCstr() const;
    std::string ToString() const;
    bool Empty() const;
    size_t Find(const char* s) const;
    size_t Find(char ch) const;

    // Операторы
    char operator[](size_t index) const;
    char& operator[](size_t index);
    operator const char*() const;

    // Методы модификации
    CowString& Append(const char* s);
    CowString& Append(const std::string& s);
    CowString Substr(size_t pos = 0, size_t count = npos) const;
    void Clear();
};

const size_t CowString::npos = -1;

// Конструкторы

CowString::CowString() : data_(nullptr) {}

CowString::CowString(const char* s) : data_(nullptr) {
    if (s && *s) {
        data_ = new Data(s);
    }
}

CowString::CowString(const std::string& s) : CowString(s.c_str()) {}

CowString::CowString(const CowString& cs) : data_(cs.data_) {
    if (data_) {
        data_->AddRef();
    }
}

CowString::CowString(CowString&& other) noexcept : data_(other.data_) {
    other.data_ = nullptr;
}

// Операторы присвоения

CowString& CowString::operator=(const CowString& other) {
    if (this != &other) {
        if (data_) data_->Release();
        data_ = other.data_;
        if (data_) data_->AddRef();
    }
    return *this;
}

CowString& CowString::operator=(CowString&& other) noexcept {
    if (this != &other) {
        if (data_) data_->Release();
        data_ = other.data_;
        other.data_ = nullptr;
    }
    return *this;
}

// Деструктор

CowString::~CowString() {
    if (data_) data_->Release();
}

// Методы доступа

size_t CowString::Size() const {
    return data_ ? strlen(data_->str) : 0;
}

const char* CowString::ToCstr() const {
    return data_ ? data_->str : "";
}

std::string CowString::ToString() const {
    if (!data_) return "";
    return std::string(data_->str, strlen(data_->str));
}

bool CowString::Empty() const {
    return !data_ || data_->str[0] == '\0';
}

size_t CowString::Find(const char* s) const {
    if (!data_ || !s) return npos;
    const char* found = strstr(data_->str, s);
    return found ? (found - data_->str) : npos;
}

size_t CowString::Find(char ch) const {
    if (!data_) return npos;
    const char* found = strchr(data_->str, ch);
    return found ? (found - data_->str) : npos;
}

// Операторы

char CowString::operator[](size_t index) const {
    if (!data_ || index >= Size()) return '\0';
    return data_->str[index];
}

char& CowString::operator[](size_t index) {

    if (data_ && data_->IsShared()) {
        Data* new_data = new Data(data_->str);
        data_->Release();
        data_ = new_data;
    }
    
    if (!data_) {
        data_ = new Data("");
    }
    
    return data_->str[index];
}

CowString::operator const char*() const {
    return data_ ? data_->str : "";
}

// Методы модификации

CowString& CowString::Append(const char* s) {
    if (!s || *s == '\0') return *this;
    
    if (!data_) {
        data_ = new Data(s);
        return *this;
    }
    
    if (data_->IsShared()) {
        Data* new_data = new Data(data_->str);
        data_->Release();
        data_ = new_data;
    }
    
    size_t old_len = Size();
    size_t add_len = strlen(s);
    size_t new_len = old_len + add_len;

    char* new_str = new char[new_len + 1];
    
    memcpy(new_str, data_->str, old_len);
    memcpy(new_str + old_len, s, add_len);
    new_str[new_len] = '\0';

    delete[] data_->str;
    data_->str = new_str;
    
    return *this;
}

CowString& CowString::Append(const std::string& s) {
    return Append(s.c_str());
}

CowString CowString::Substr(size_t pos, size_t count) const {
    if (!data_ || pos >= Size()) return CowString();
    
    size_t len = Size() - pos;
    if (count != npos && count < len) {
        len = count;
    }
    
    if (len == 0) return CowString();
    
    char* buffer = new char[len + 1];
    memcpy(buffer, data_->str + pos, len);
    buffer[len] = '\0';
    
    CowString result(buffer);
    delete[] buffer;
    
    return result;
}

void CowString::Clear() {
    if (data_) {
        data_->Release();
        data_ = nullptr;
    }
}



