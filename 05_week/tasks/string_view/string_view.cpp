#include <cstring>
#include <limits>
#include <string>

class StringView {
public:
    inline static size_t npos = std::numeric_limits<size_t>::max();
    
    StringView() = default;
    
    StringView(const std::string& str, size_t start = 0, size_t len = npos) {
        if (start > str.size() || str.empty()) {
            return;
        }

        if (len == npos || start + len > str.size()) {
            len = str.size() - start;
        } 

        begin_ = str.data() + start;
        end_ = begin_ + len;
    };

    StringView(const char* str) : begin_(str ? str : nullptr), end_(str ? str + std::strlen(str) : nullptr) {}

    StringView(const char* str, size_t len) {
        if (!str) {
            return;
        }

        size_t strLen = std::strlen(str);
        if (len > strLen) {
            len = strLen;
        }

        begin_ = str;
        end_ = str + len;
    }

    const char& operator[](size_t idx) const {
        return begin_[idx];
    }

    const char* Data() const;
    const char& Front() const;
    const char& Back() const;
    size_t Size() const;
    size_t Length() const;
    bool Empty() const;
    int Compare(StringView& str) const;
    void RemovePrefix(size_t len);
    void RemoveSuffix(size_t len);
    StringView Substr(size_t start, size_t len) const;
    size_t Find(char symbol, size_t start) const;
    size_t Find(const StringView& str, size_t start) const;
    std::string ToString() const;
    
private:
    const char* begin_ = nullptr;
    const char* end_ = nullptr;
};


bool operator==(StringView& lhs, StringView& rhs) {
    return std::strcmp(lhs.Data(), rhs.Data()) == 0;
}

const char* StringView::Data() const {
    return begin_;
}

const char& StringView::Front() const {
    return *begin_;
}

const char& StringView::Back() const {
    return *(end_ - 1);
}

size_t StringView::Size() const {
    return end_ - begin_;
}

size_t StringView::Length() const {
    return Size();
}

bool StringView::Empty() const {
    if (begin_ == end_ || begin_ == nullptr) {
        return true;
    }

    return false;
}

int StringView::Compare(StringView& str) const {
    return std::strcmp(begin_, str.begin_);
}

void StringView::RemovePrefix(size_t len) {
    if (begin_ + len >= end_) {
        begin_ = end_;
        return;
    }

    begin_ += len;
}

void StringView::RemoveSuffix(size_t len) {
    if (end_ - len <= begin_) {
        end_ = begin_;
        return;
    }

    end_ -= len;
}

StringView StringView::Substr(size_t start = 0, size_t len = 0) const {
    if (start > Size() || Empty()) {
        return StringView();
    }

    if (len == 0) {
        return StringView(begin_ + start);
    }

    return StringView(begin_ + start, len);
}

size_t StringView::Find(char symbol, size_t start = 0) const {
    if (start > Size() || Empty()) {
        return npos;
    }

    const char* pos = std::strchr(begin_ + start, symbol);

    if (!pos) {
        return npos;
    } 

    return pos - begin_;
}

size_t StringView::Find(const StringView& str, size_t start = 0) const {
    if (str.Empty()) {
        return 0;
    }

    if (start > Size() || str.Size() > Size() || Empty()) {
        return npos;
    }

    const char* pos = std::strstr(begin_ + start, str.begin_);

    if (!pos) {
        return npos;
    }

    return pos - begin_;
}

std::string StringView::ToString() const {
    return std::string(begin_, Size());
}
