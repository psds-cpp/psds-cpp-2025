#include "cow_string.hpp"

CowString::Description::Description(const char* str, const size_t len)
    : data(new char[len + 1]), size(len), ref_count(1) {
    if (str && size > 0) {
        std::strcpy(data, str);
    }
    data[size] = '\0';
}

CowString::Description::~Description() {
    delete[] data;
}

CowString::Description* CowString::CreateEmpty() {
    return new Description("", 0);
}

void CowString::Release() const {
    if (--description_->ref_count == 0) {
        delete description_;
    }
}

CowString::CowString() : description_(CreateEmpty()) {}

CowString::CowString(const char* str) {
    if (str) {
        size_t len = std::strlen(str);
        description_ = new Description(str, len);
    } else {
        description_ = CreateEmpty();
    }
}

CowString::CowString(const std::string& str)
    : description_(new Description(str.c_str(), str.length())) {}

CowString::CowString(const CowString& other) : description_(other.description_) {
    description_->ref_count++;
}

CowString& CowString::operator=(const CowString& other) {
    if (this != &other) {
        Release();
        description_ = other.description_;
        description_->ref_count++;
    }
    return *this;
}

CowString::CowString(CowString&& other) noexcept : description_(other.description_) {
    other.description_ = CreateEmpty();
}

CowString& CowString::operator=(CowString&& other) noexcept {
    if (this != &other) {
        Release();
        description_ = other.description_;
        other.description_ = CreateEmpty();
    }
    return *this;
}

CowString::~CowString() {
    if (--description_->ref_count == 0) {
        delete description_;
    }
}

size_t CowString::Size() const {
    return description_->size;
}

const char* CowString::ToCstr() const {
    return description_->data;
}

std::string CowString::ToString() const {
    return {description_->data, description_->size};
}

char CowString::operator[](size_t index) const {
    return description_->data[index];
}

CowString::operator const char*() const {
    return description_->data;
}

bool CowString::Empty() const {
    return description_->size == 0;
}

size_t CowString::Find(const char* substr) const {
    if (!substr || *substr == '\0') {
        return 0;
    }
    const char* pos = std::strstr(description_->data, substr);
    if (pos) {
        return pos - description_->data;
    }
    return npos;
}

size_t CowString::Find(char ch) const {
    const char* pos = std::strchr(description_->data, ch);
    if (pos) {
        return pos - description_->data;
    }
    return npos;
}

char& CowString::operator[](size_t index) {
    if (description_->ref_count > 1) {
        description_->ref_count--;
        description_ = new Description(description_->data, description_->size);
    }
    return description_->data[index];
}

CowString& CowString::Append(const char* str) {
    if (!str || *str == '\0') {
        return *this;
    }

    size_t append_len = std::strlen(str);
    size_t new_size = description_->size + append_len;

    auto* new_data = new Description("", new_size);
    std::strcpy(new_data->data, description_->data);
    std::strcpy(new_data->data + description_->size, str);
    new_data->data[new_size] = '\0';

    Release();
    description_ = new_data;

    return *this;
}

CowString& CowString::Append(const std::string& str) {
    return Append(str.c_str());
}

CowString CowString::Substr(const size_t pos, const size_t count) const {
    if (pos >= description_->size) {
        return {};
    }

    size_t substr_length = count;
    if (count == npos || (pos + count) > description_->size) {
        substr_length = description_->size - pos;
    }

    auto* temp = new char[substr_length + 1];
    std::strncpy(temp, description_->data + pos, substr_length);
    temp[substr_length] = '\0';

    CowString result(temp);
    delete[] temp;

    return result;
}

void CowString::Clear() {
    Release();
    description_ = CreateEmpty();
}