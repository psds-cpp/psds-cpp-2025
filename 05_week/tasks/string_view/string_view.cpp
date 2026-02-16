#include "string_view.hpp"

StringView::StringView(const std::string& str, const size_t begin, const size_t length) {
    if (begin > str.length()) return;
    data_ = str.data() + begin;
    const size_t start_sub = str.length() - begin;
    size_ = (length > start_sub || length == npos) ? start_sub : length;
}

StringView::StringView(const char* str) {
    if (str == nullptr) return;
    data_ = str;
    size_ = strlen(str);
}

StringView::StringView(const char* str, const size_t length) : data_(str) {
    if (str == nullptr) return;
    data_ = str;
    size_ = length;
}

char StringView::operator[](size_t index) const {
    // potential UB
    return data_[index];
}

const char* StringView::Data() const {
    return data_;
}

char StringView::Front() const {
    // potential UB
    return *data_;
}

char StringView::Back() const {
    // potential UB
    return *(data_ + size_ - 1);
}

size_t StringView::Size() const {
    return size_;
}

size_t StringView::Length() const {
    return size_;
}

bool StringView::Empty() const {
    return size_ == 0;
}

StringView StringView::Substr(const size_t begin, const size_t length) const {
    if (begin >= size_) return {};

    const size_t start_sub = size_ - begin;
    const size_t sub_length = (length == npos || length > start_sub) ? start_sub : length;

    return {data_ + begin, sub_length};
}

size_t StringView::Find(const char pattern, const size_t begin_index) const {
    if (data_ == nullptr || begin_index >= size_) {
        return npos;
    }

    for (size_t i = begin_index; i < size_; ++i) {
        if (data_[i] == pattern) {
            return i;
        }
    }

    return npos;
}

size_t StringView::Find(const StringView& pattern, size_t begin_index) const {
    if (pattern.Empty()) {
        return begin_index;
    }

    if (data_ == nullptr || begin_index >= size_ || pattern.Size() > (size_ - begin_index)) {
        return npos;
    }

    for (size_t i = begin_index; i <= size_ - pattern.Size(); ++i) {
        bool found = true;
        for (size_t j = 0; j < pattern.Size(); ++j) {
            if (data_[i + j] != pattern[j]) {
                found = false;
                break;
            }
        }
        if (found) {
            return i;
        }
    }

    return npos;
}

std::string StringView::ToString() const {
    if (data_ == nullptr) return {};
    return {data_, size_};
}

void StringView::RemovePrefix(const size_t length) {
    if (length >= size_) {
        data_ = nullptr;
        size_ = 0;
    } else {
        data_ += length;
        size_ -= length;
    }
}

void StringView::RemoveSuffix(const size_t length) {
    size_ = length < size_? size_ - length : 0;
}
