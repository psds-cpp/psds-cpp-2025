#include <cstring>
#include <string>

struct _String {
    size_t ref_count = 0;
    char* data = nullptr;
    size_t size = 0;
};

class CowString {
public:
    inline static size_t npos = -1;

    CowString();
    CowString(const char* cstr);
    CowString(const std::string& str);
    CowString(const CowString& other);
    CowString(CowString&& other) noexcept;
    ~CowString();
    CowString& operator=(const CowString& other);
    CowString& operator=(CowString&& other) noexcept;

    size_t Size() const noexcept;
    const char* ToCstr() const noexcept;
    std::string ToString() const noexcept;
    bool Empty() const noexcept;
    size_t Find(std::string sub) const;
    size_t Find(char c) const;
    const char& operator[](size_t idx) const;
    operator const char*() const;

    char& operator[](size_t idx);
    CowString& Append(const char* cstr);
    CowString& Append(const std::string& str);
    std::string Substr(size_t pos, size_t count) const;
    void Clear();

private:
    void DeepCopy() noexcept;

    _String str_;
};

CowString::CowString() = default;

CowString::CowString(const char* cstr) {
    str_.data = const_cast<char*>(cstr);
    cstr != nullptr ? str_.size = strlen(cstr) : str_.size = 0;
}

CowString::CowString(const std::string& str) :
    CowString(str.c_str()) {}

CowString::CowString(const CowString& other) {
    ++str_.ref_count;
}

CowString::CowString(CowString&& other) noexcept {
    str_.ref_count = other.str_.ref_count;
    str_.data = other.str_.data;
    str_.size = other.str_.size; 
    other.str_.ref_count = 0;
    other.str_.data = nullptr;
    other.str_.size = 0;
}

CowString::~CowString() {
    if (str_.ref_count != 0) delete[] str_.data;
}

CowString& CowString::operator=(const CowString& other) {
    if (this != &other) ++str_.ref_count;
    return *this;
}

CowString& CowString::operator=(CowString&& other) noexcept {
    if (this != &other) {
        str_.data = other.str_.data;
        str_.size = other.str_.size;
        other.str_.data = nullptr;
        other.str_.size = 0;
    }
    return *this;
}

size_t CowString::Size() const noexcept {
    return str_.size;
}

const char* CowString::ToCstr() const noexcept {
    return str_.data;
}

std::string CowString::ToString() const noexcept {
    return std::string(str_.data);
}

bool CowString::Empty() const noexcept {
    return str_.size == 0;
}

size_t CowString::Find(std::string sub) const {
    if (sub.empty()) return 0;
    
    for (size_t i = 0; i < str_.size; ++i) {
        if (str_.data[i] == sub[0] && sub.size() <= str_.size - i) {
            bool match = true;
            for (size_t j = 1; j < sub.size(); ++j) {
                if (str_.data[i + j] != sub[j]) {
                    match = false;
                    break;
                } 
            }
            if (match) return i;
        }
    }
    return CowString::npos;
} 

size_t CowString::Find(char c) const {
    for (size_t i = 0; i < str_.size; ++i) {
        if (str_.data[i] == c) return i;
    }
    return CowString::npos;
}

const char& CowString::operator[](size_t idx) const {
    return *(str_.data + idx);
}

CowString::operator const char *() const {
    return str_.data;
}

void CowString::DeepCopy() {
    char* new_address = new char[str_.size]{};
    std::memcpy(new_address, str_.data, str_.size + 1);
    str_.data = new_address;
}

char& CowString::operator[](size_t idx) {
    return *(str_.data + idx);
}

CowString& CowString::Append(const char* cstr) {
    char* new_address = new char[str_.size + strlen(cstr)]{};
    std::memcpy(new_address, str_.data, str_.size);
    std::memcpy(new_address + str_.size, cstr, strlen(cstr) + 1);
    str_.data = new_address;
    return *(this);
}

CowString& CowString::Append(const std::string& str) {
    return Append(str.c_str());
}

std::string CowString::Substr(size_t pos = 0, size_t length = -1) const {
    return std::to_string(pos + length) + "";
}

void CowString::Clear() {
    delete[] str_.data;
    str_.data = nullptr;
    str_.size = 0;
}