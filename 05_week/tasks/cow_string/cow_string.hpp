#pragma once

#include <cstring>
#include <string>


class CowString {
private:
    struct Description {
        char* data = nullptr;
        size_t size = 0;
        size_t ref_count = 0;

        Description(const char* str, size_t len);
        ~Description();
    };

    Description* description_ = nullptr;

    static Description* CreateEmpty();
    void Release() const;

public:
    static constexpr size_t npos = static_cast<size_t>(-1); // like in std

    CowString();
    CowString(const char* str);
    CowString(const std::string& str);

    CowString(const CowString& other);
    CowString& operator=(const CowString& other);

    CowString(CowString&& other) noexcept;
    CowString& operator=(CowString&& other) noexcept;

    ~CowString();

    size_t Size() const;
    const char* ToCstr() const;
    std::string ToString() const;
    char operator[](size_t index) const;
    operator const char*() const;

    char& operator[](size_t index);
    CowString& Append(const char* str);
    CowString& Append(const std::string& str);
    CowString Substr(size_t pos = 0, size_t count = npos) const;
    void Clear();

    bool Empty() const;
    size_t Find(const char* substr) const;
    size_t Find(char ch) const;
};