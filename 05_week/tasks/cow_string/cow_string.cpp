#include <cstring>
#include <string>

class CowString {
public:
    CowString();
    CowString(const char* cstr);
    CowString(const std::string& str);
    CowString(const CowString& other);
    CowString(CowString&& other) noexcept;
    CowString& operator=(const CowString& other);
    CowString& operator=(CowString&& other) noexcept;
    ~CowString();
    size_t Size() const noexcept { return cow_string_->size; }
    char* ToCstr() const noexcept { return cow_string_->data; }
    std::string ToString() const noexcept {return std::string(cow_string_->data); }
    const char& operator[](size_t index) const;
    char& operator[](size_t index);
    operator const char*() const;
    CowString& Append(const char* cstr);
    CowString& Append(const std::string& str);
    CowString Substr(size_t pos, size_t length);
    void Clear();
    bool Empty() const noexcept;
    size_t Find(const char* cstr, size_t pos) const;
    size_t Find(const char c, size_t pos) const;
    static constexpr size_t npos = -1;

private:
    struct cow_string {
        char* data = nullptr;
        size_t size = 0;
        size_t ref_count = 1;

        cow_string(size_t size):
            data(new char[size + 1]), 
            size(size), 
            ref_count(1) {
            data[size] = '\0';
        }
        ~cow_string() { delete[] data; }
    };

    cow_string* cow_string_;
};

CowString::CowString():
    cow_string_(new cow_string(0)) {}

CowString::CowString(const char* cstr):
    cow_string_(new cow_string(std::strlen(cstr))) {
    std::memcpy(cow_string_->data, cstr, cow_string_->size);
}

CowString::CowString(const std::string& str):
    cow_string_(new cow_string(str.size())) {
    std::memcpy(cow_string_->data, str.data(), cow_string_->size);
}

CowString::CowString(const CowString& other):
    cow_string_(other.cow_string_) {
    ++(cow_string_->ref_count);
}

CowString::CowString(CowString&& other) noexcept:
    cow_string_(other.cow_string_) {
    other.cow_string_ = new cow_string(0);
}

CowString& CowString::operator=(const CowString& other) {
    if(this->cow_string_ != other.cow_string_) {
        if(cow_string_->ref_count == 1) {
            delete cow_string_;
        }
        cow_string_ = other.cow_string_;
        ++cow_string_->ref_count;
    }
    return *this;
}

CowString& CowString::operator=(CowString&& other) noexcept {
    if(this->cow_string_ != other.cow_string_) {
        if(cow_string_->ref_count == 1) {
            delete cow_string_;
        }
        cow_string_ = other.cow_string_;
        other.cow_string_ = new cow_string(0);
    }
    return *this;
}

CowString::~CowString() {
    --(cow_string_->ref_count);
    if((cow_string_->ref_count) == 0) delete cow_string_;
}

const char& CowString::operator[](size_t index) const {
    return cow_string_->data[index];
}

char& CowString::operator[](size_t index) {
    if(cow_string_->ref_count == 1){
        return cow_string_->data[index];
    }
    --(cow_string_->ref_count);
    cow_string* tmp = cow_string_;
    cow_string_ = new cow_string(cow_string_->size);
    std::memcpy(cow_string_->data, tmp->data, cow_string_->size);
    return cow_string_->data[index];
}

CowString::operator const char*() const {
    return cow_string_->data;
}

CowString& CowString::Append(const char* cstr) {
    if(std::strlen(cstr) != 0) {
        cow_string* tmp = cow_string_;
        cow_string_ = new cow_string(cow_string_->size + std::strlen(cstr));
        std::memcpy(cow_string_->data, tmp->data, tmp->size);
        std::memcpy(cow_string_->data + tmp->size, cstr, std::strlen(cstr));
        --(tmp->ref_count);
        if(tmp->ref_count == 0){
            delete tmp;
        }
    }
    return *this;
}

CowString& CowString::Append(const std::string& str) {
    return Append(str.c_str());
}

CowString CowString::Substr(size_t pos = 0, size_t length = npos) {
    if(pos > cow_string_->size || length == 0) {
        return CowString();
    }
    length = std::min(length, cow_string_->size - pos);
    return CowString(std::string(cow_string_->data + pos, length));
}
    
void CowString::Clear() {
    cow_string* tmp = cow_string_;
    cow_string_ = new cow_string(0);
    --(tmp->ref_count);
    if(tmp->ref_count == 0){
        delete tmp;
    }
}

bool CowString::Empty() const noexcept {
    return cow_string_->size == 0;
}
size_t CowString::Find(const char* cstr, size_t pos = 0) const {
    if (Empty()) {
        return npos;
    }

    pos = std::min(pos, cow_string_->size);
    for (size_t i = pos; i < cow_string_->size - std::strlen(cstr) + 1; ++i) {
        if (std::memcmp(cow_string_->data + i, cstr, std::strlen(cstr)) == 0) {
            return i;
        }
    }
    return npos;
}

size_t CowString::Find(const char c, size_t pos = 0) const {
    if (Empty()) {
        return npos;
    }

    pos = std::min(pos, cow_string_->size);
    for (size_t i = pos; i < cow_string_->size; ++i) {
        if(cow_string_->data[i] == c) {
            return i;
        }
    }
    return npos;
}