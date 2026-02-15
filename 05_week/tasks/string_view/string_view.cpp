#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <stddef.h>

class StringView {
public:
    StringView();
    StringView(const std::string& str, size_t begin = 0, size_t len = npos);
    StringView(const char* str);
    StringView(const char* str, size_t len);
    const char* Data() const;
    char Front() const;
    char Back() const;
    size_t Size() const;
    size_t Length() const;
    bool Empty() const;
    void RemovePrefix(size_t k);
    void RemoveSuffix(size_t k);
    StringView Substr(size_t begin, size_t len = npos) const;
    size_t Find(char x, size_t begin = 0) const;
    size_t Find(const char* x, size_t begin = 0) const;
    size_t Find(const StringView& x, size_t begin = 0) const;
    std::string ToString() const;
    char operator[](int pos) const;
    inline const static size_t npos = static_cast<size_t>(-1);
private:
    static size_t m_clampLen(size_t begin, size_t len, size_t total);
    size_t m_size = 0;
    const char* m_str_ptr = nullptr;
};

size_t StringView::m_clampLen(size_t begin, size_t len, size_t total) {
    if (begin >= total) { return 0; }
    size_t max_len = total - begin;
    if (len == npos || len > max_len) { return max_len; }
    return len;
}

StringView::StringView() {}

StringView::StringView(const std::string& str, size_t begin, size_t len) : m_size(m_clampLen(begin, len, str.length())) {
    if (m_size == 0) { return; }
    m_str_ptr = str.data() + begin;
}

StringView::StringView(const char* str) : m_size(str == nullptr ? 0 : std::strlen(str)), m_str_ptr(str) {}

StringView::StringView(const char* str, size_t len) : m_size(len), m_str_ptr(str) {
    if (str == nullptr) { m_size = 0; }
    else if (len == npos) { m_size = std::strlen(str); }
}

const char* StringView::Data() const {
    return m_str_ptr;
}

char StringView::Front() const {
    return m_str_ptr[0];
}

char StringView::Back() const {
    return m_str_ptr[m_size - 1];
}

size_t StringView::Size() const {
    return m_size;
}

size_t StringView::Length() const {
    return m_size;
}

bool StringView::Empty() const {
    return m_size == 0;
}

void StringView::RemovePrefix(size_t k) {
    if (k > m_size) { k = m_size; }
    m_str_ptr += k;
    m_size -= k;
}

void StringView::RemoveSuffix(size_t k) {
    if (k > m_size) { k = m_size; }
    m_size -= k;
}

StringView StringView::Substr(size_t begin, size_t len) const {
    size_t new_len = m_clampLen(begin, len, m_size);
    if (new_len == 0) { return StringView(); }
    return StringView(m_str_ptr + begin, new_len);
}

size_t StringView::Find(char needle, size_t begin) const {
    for (size_t i = begin; i < m_size; ++i) {
        if (m_str_ptr[i] == needle) { return i; }
    }
    return npos;
}

size_t StringView::Find(const char* needle, size_t begin) const {
    if (!needle) { return begin; }
    size_t m = strlen(needle);
    if (m == 0) { return begin; }
    if (m > m_size || begin > m_size - m) { return npos; }
    for (size_t i = begin; i <= m_size - m; ++i) {
        if (memcmp(m_str_ptr + i, needle, m) == 0) { return i; }
    }
    return npos;
}

size_t StringView::Find(const StringView& needle, size_t begin) const {
    return Find(needle.m_str_ptr, begin);
}

std::string StringView::ToString() const {
    return std::string(m_str_ptr, m_size);
}

char StringView::operator[](int pos) const {
    return m_str_ptr[pos];
}
