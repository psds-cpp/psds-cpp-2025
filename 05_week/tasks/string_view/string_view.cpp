#include <cstring>
#include <string>
#include <algorithm>

class StringView {
public:
    static inline constexpr size_t npos = -1;

    // Конструкторы (объявления)
    StringView();
    StringView(const std::string& str, size_t pos = 0, size_t len = npos);
    StringView(const char* str);
    StringView(const char* str, size_t len);
    const char& operator[](size_t idx) const;
    const char* Data() const;
    const char& Front() const;
    const char& Back() const;
    size_t Size() const;
    size_t Length() const;
    bool Empty() const;
    void RemovePrefix(size_t n);
    void RemoveSuffix(size_t n);
    StringView Substr(size_t pos, size_t len = npos) const;
    size_t Find(char symbol, size_t pos) const;
    size_t Find(StringView sv, size_t pos) const;
    std::string ToString() const;

private:
    const char* data;
    size_t size;
};

StringView::StringView(const std::string& str, size_t pos, size_t len) {
        if (pos >= str.size()) {
            data = nullptr;
            size = 0;
        }
        else {
            data = str.data() + pos;
            size = std::min(len, str.size() - pos);
        }
    }

StringView::StringView(const char* str) : data(str), size(str ? std::strlen(str) : 0) {}

StringView::StringView(const char* str, size_t len) : data(str), size((str) ? len : 0) {}

StringView::StringView() : data(nullptr), size(0) {}

const char& StringView::operator[](size_t idx) const {
    return data[idx];
}

const char* StringView::Data() const {
    return data;
}

const char& StringView::Front() const {
    return data[0];
}

const char& StringView::Back() const {
    return data[size - 1];
}

size_t StringView::Size() const {
    return size;
}

size_t StringView::Length() const {
    return size;
}

bool StringView::Empty() const {
    return data == nullptr || size == 0;
}

void StringView::RemovePrefix(size_t len) {
    if (len > size) {
        data = nullptr;
        size = 0;
    }
    else {
        data += len;
        size -= len;
    }   
}

void StringView::RemoveSuffix(size_t len) {
    size -= (len > size) ? size : len;
}

StringView StringView::Substr(size_t pos, size_t len) const {
    if (pos >= size) {
        return StringView();
    }
    return StringView(data + pos, std::min(len, size - pos));
}

size_t StringView::Find(char symbol, size_t pos = 0) const {
    for (size_t i = pos; i < size; ++i) {
        if (data[i] == symbol) {
            return i;
        }
    }
    return npos;
}

size_t StringView::Find(StringView sv, size_t pos = 0) const {
    if (sv.size > size - pos || (data == nullptr || pos >= size)) {
        return npos;
    }
    if (sv.size == 0) {
        return pos;
    }
    for (size_t i = pos; i <= size - sv.size; ++i) {
        if (std::memcmp(data + i, sv.data, sv.size) == 0) {
            return i;
        }
    }
    return npos;
}

std::string StringView::ToString() const {
    return (data) ? std::string(data, size) : std::string();
}