#include <cstring>
#include <string>
#include <stddef.h>

struct SharedString {
    SharedString() = default;
    SharedString(size_t size, const char* src);
    size_t ref_count = 1;
    size_t size = 0;
    char* data = nullptr;
};

class CowString {
public:
    ~CowString();
    CowString();
    CowString(const char* str);
    CowString(const std::string& str);
    CowString(const CowString& other);
    CowString(CowString&& other);
    CowString& operator=(const CowString& other);
    CowString& operator=(CowString&& other);
    operator const char*() const;
    char operator[](size_t pos) const;
    char& operator[](size_t pos);
    size_t Size() const;
    const char* ToCstr() const;
    std::string ToString() const;
    bool Empty() const;
    CowString& Append(const std::string& str);
    void Clear();
    CowString Substr(size_t begin = 0, size_t len = npos) const;
    size_t Find(char needle, size_t begin = 0) const;
    size_t Find(const char* needle, size_t begin = 0) const;
    inline const static size_t npos = static_cast<size_t>(-1);
private:
    static size_t m_clampLen(size_t begin, size_t len, size_t total);
    void m_decrementRefCount();
    void m_detach();
    void m_detach(size_t size, const char* src);
    SharedString* m_ptr = nullptr;
};

SharedString::SharedString(size_t size, const char* src) : size(size), data(new char[size + 1]{}) {
    std::strcpy(data, src);
}

size_t CowString::m_clampLen(size_t begin, size_t len, size_t total) {
    if (begin >= total) { return 0; }
    size_t max_len = total - begin;
    if (len == npos || len > max_len) { return max_len; }
    return len;
}

void CowString::m_decrementRefCount() {
    if (!m_ptr) { return; }
    m_ptr->ref_count -= 1;
    if (m_ptr->ref_count != 0) { return; }
    delete[] m_ptr->data;
    delete m_ptr;
}

void CowString::m_detach() {
    if (m_ptr->ref_count == 1) { return; }
    m_ptr->ref_count -= 1;
    m_ptr = new SharedString(m_ptr->size, m_ptr->data);
}

void CowString::m_detach(size_t size, const char* src) {
    if (m_ptr->ref_count == 1) {
        if (size > m_ptr->size) {
            delete[] m_ptr->data;
            m_ptr->data = new char[size + 1];
        }
        m_ptr->size = size;
        std::strcpy(m_ptr->data, src);
        return;
    }
    m_ptr->ref_count -= 1;
    m_ptr = new SharedString(size, src);
}

CowString::~CowString() {
    m_decrementRefCount();
}

CowString::CowString() : m_ptr(new SharedString(0, "")) {}

CowString::CowString(const char* str) : m_ptr(new SharedString(std::strlen(str), str)) {}

CowString::CowString(const std::string& str) : m_ptr(new SharedString(str.length(), str.c_str())) {}

CowString::CowString(const CowString& other) : m_ptr(other.m_ptr) {
    m_ptr->ref_count += 1;
}

CowString::CowString(CowString&& other) : m_ptr(other.m_ptr) {
    other.m_ptr = new SharedString(0, "");
}

CowString& CowString::operator=(const CowString& other) {
    if (this == &other) { return *this; }
    m_decrementRefCount();
    m_ptr = other.m_ptr;
    m_ptr->ref_count += 1;
    return *this;
}

CowString& CowString::operator=(CowString&& other) {
    if (this == &other) { return *this; }
    m_decrementRefCount();
    m_ptr = other.m_ptr;
    other.m_ptr = new SharedString(0, "");
    return *this;
}

CowString::operator const char* () const {
    return m_ptr->data;
}

char CowString::operator[](size_t pos) const {
    return m_ptr->data[pos];
}

char& CowString::operator[](size_t pos) {
    m_detach();
    return m_ptr->data[pos];
}

size_t CowString::Size() const {
    return m_ptr->size;
}

const char* CowString::ToCstr() const {
    return m_ptr->data;
}

std::string CowString::ToString() const {
    return std::string(m_ptr->data);
}

bool CowString::Empty() const {
    return m_ptr->size == 0;
}

CowString& CowString::Append(const std::string& str) {
    size_t new_size = m_ptr->size + str.length();
    if (m_ptr->size == new_size) { return *this; }

    char new_str[new_size + 1] = {};
    std::strcpy(new_str, m_ptr->data);
    std::strcat(new_str, str.c_str());
    m_detach(new_size, new_str);

    return *this;
}

void CowString::Clear() {
    m_detach(0, "");
}

CowString CowString::Substr(size_t begin, size_t len) const {
    size_t new_len = m_clampLen(begin, len, m_ptr->size);
    if (new_len == 0) { return CowString(); }
    char substr[new_len + 1] = {};
    memcpy(substr, m_ptr->data + begin, new_len);
    return CowString(substr);
}

size_t CowString::Find(char needle, size_t begin) const {
    char str[2] = {needle, '\0'};
    return Find(str, begin);
}

size_t CowString::Find(const char* needle, size_t begin) const {
    if (!needle) { return begin; }
    size_t m = std::strlen(needle);
    if (m == 0) { return begin; }
    if (m > m_ptr->size || begin > m_ptr->size - m) { return npos; }
    for (size_t i = begin; i <= m_ptr->size - m; ++i) {
        if (memcmp(m_ptr->data + i, needle, m) == 0) { return i; }
    }
    return npos;
}
