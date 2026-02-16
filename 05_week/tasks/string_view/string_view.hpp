#pragma once

#include <cstring>
#include <string>

class StringView {
private:
    const char* data_ = nullptr;
    size_t size_ = 0;

public:
    static constexpr size_t npos = static_cast<size_t>(-1); // like in std

    StringView() = default;
    StringView(const std::string& str, size_t begin = 0, size_t length = npos);
    StringView(const char* str);
    StringView(const char* str, size_t length);

    char operator[](size_t index) const;

    const char* Data() const;
    char Front() const;
    char Back() const;
    size_t Size() const;
    size_t Length() const;
    bool Empty() const;
    StringView Substr(size_t begin, size_t length = npos) const;
    size_t Find(char pattern, size_t begin_index = 0) const;
    size_t Find(const StringView& pattern, size_t begin_index = 0) const;
    std::string ToString() const;

    void RemovePrefix(size_t length);
    void RemoveSuffix(size_t length);
};