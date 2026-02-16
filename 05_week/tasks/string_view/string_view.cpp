#include <cstring>
#include <string>

class StringView {
public: 
    inline static size_t npos = -1;

    StringView();
    StringView(const std::string& str, size_t pos_sub, size_t len_sub);
    StringView(const char* cstr);
    StringView(const char* cstr, size_t len);

    const char& operator[](size_t idx) const;
    const char* Data() const noexcept;
    const char& Front() const noexcept;
    const char& Back() const noexcept;
    size_t Size() const noexcept;
    size_t Length() const noexcept;
    bool Empty() const noexcept;
    void RemovePrefix(size_t count);
    void RemoveSuffix(size_t count);
    StringView Substr(size_t pos, size_t count) const;
    size_t Find(char c, size_t pos) const;
    size_t Find(StringView sub, size_t pos) const;
    std::string ToString() const noexcept;

private:
    const char* data_ = nullptr;
    size_t size_ = 0;
};

StringView::StringView() = default;

StringView::StringView(const std::string& str, size_t pos_sub = 0, size_t len_sub = StringView::npos) {
    if (pos_sub >= str.length()) StringView();
    else {
        data_ = str.data() + pos_sub; 
        len_sub > str.length() ? size_ = str.length() - pos_sub : size_ = len_sub;
    }
}

StringView::StringView(const char* cstr, size_t len) :
    data_(cstr) {
    if (cstr == nullptr) size_ = 0;
    else  len > strlen(cstr) ? size_ = strlen(cstr) : size_ = len;
}

StringView::StringView(const char* cstr) :
    data_(cstr) {
    cstr != nullptr ? size_ = strlen(cstr) : size_ = 0;
} 

const char& StringView::operator[](size_t idx) const {
    return *(data_ + idx);
}

const char* StringView::Data() const noexcept {
    return data_;
}

const char& StringView::Front() const noexcept {
    return *data_;
}

const char& StringView::Back() const noexcept {
    return *(data_ + size_ - 1);
}

size_t StringView::Size() const noexcept {
    return size_;
}

size_t StringView::Length() const noexcept {
    return size_;
}
    
bool StringView::Empty() const noexcept {
    return size_ == 0;
}

void StringView::RemovePrefix(size_t count) {
    count > size_ ? (data_ += size_, size_ = 0) : (data_ += count, size_ -= count);
}

void StringView::RemoveSuffix(size_t count) {
    count > size_ ? size_ = 0 : size_ -= count;
}

std::string StringView::ToString() const noexcept {
    return data_ != nullptr ? std::string(data_, size_) : std::string("");
}

StringView StringView::Substr(size_t pos, size_t count = StringView::npos) const {
    return (pos < size_) ? StringView(data_ + pos, count) : StringView();
}

size_t StringView::Find(char c, size_t pos = 0) const {
    for (auto i = pos; i < size_; ++i) {
        if (data_[i] == c) return i;
    }
    return StringView::npos;
}

size_t StringView::Find(StringView sub, size_t pos = 0) const {
    if (sub.Empty()) return 0;
    
    for (size_t i = pos; i < size_; ++i) {
        if (data_[i] == sub[0] && sub.Size() <= size_ - i) {
            bool match = true;
            for (size_t j = 1; j < sub.Size(); ++j) {
                if (data_[i + j] != sub[j]) {
                    match = false;
                    break;
                } 
            }
            if (match) return i;
        }
    }
    return StringView::npos;
}