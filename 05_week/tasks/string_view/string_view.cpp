#include <cstring>
#include <string>

class StringView {
public:
    StringView() = default;
    StringView(const std::string& str, size_t begin, size_t len_substr);
    StringView(const char* cstr, size_t len_substr = 0);
    const char& operator[](size_t index) const;
    const char* Data() const { return data_ + begin_; }
    const char& Front() const { return *(data_ + begin_); }
    const char& Back() const { return *(data_ + begin_ + len_substr_); }
    size_t Size() const { return len_substr_; }
    size_t Length() const { return len_substr_; }
    bool Empty() const { return len_substr_ == 0; }
    void RemovePrefix(size_t count) { begin_ += count; }
    void RemoveSuffix(size_t count) { len_substr_ -= count; }
    StringView Substr(size_t begin = 0, size_t len = npos) const;
    size_t Find(StringView strview, size_t pos = 0) const;
    size_t Find(char c, size_t pos = 0) const;
    std::string ToString() const;
    int Compare(StringView other) const;
    static const size_t npos;

private:
    const char* data_ = nullptr;
    size_t len_data_ = 0;
    size_t begin_ = 0;
    size_t len_substr_ = 0;
};

const size_t StringView::npos = -1;

StringView::StringView(const std::string& str, size_t begin = 0, size_t len_substr = 0):
    data_(str.data()),
    len_data_(str.size()),
    begin_(begin),
    len_substr_(std::min(len_substr, len_data_ - begin)) {
    if(begin >= len_data_){
        begin_ = 0;
        len_substr_ = len_data_;
    }
}

StringView::StringView(const char* cstr, size_t len_substr) {
    if(cstr) {
        data_ = cstr;
        len_data_ = std::strlen(cstr);
        len_substr_ = std::min(len_substr, len_data_);
    }
}

const char& StringView::operator[](size_t index) const {
    return index > len_substr_ ? *(data_ + len_data_) : *(data_ + index);
}

StringView StringView::Substr(size_t begin, size_t len) const {
    return begin < len_substr_ ? StringView(data_ + begin, len) : StringView(data_, 0);
}
size_t StringView::Find(StringView strview, size_t pos) const {
    pos = std::min(pos, len_substr_);
    if (Empty() || strview.Empty() || strview.Size() > len_substr_ - pos) {
        return npos;
    }

    for (size_t i = pos; i <= len_substr_ - strview.Size(); ++i) {
        if (std::memcmp(data_ + begin_ + i, strview.Data(), strview.Size()) == 0) {
            return i;
        }
    }
    return npos;
}
size_t StringView::Find(char c, size_t pos) const {
    if (Empty()) {
        return npos;
    }

    pos = std::min(pos, len_substr_);
    for (size_t i = pos; i <= len_substr_; ++i) {
        if (*(data_ + begin_ + i) == c) {
            return i;
        }
    }
    return npos;
};
std::string StringView::ToString() const {
    return std::string(data_, len_substr_);
}

int StringView::Compare(StringView other) const {
    size_t n = std::min(this->len_substr_, other.len_substr_);
    int strcmp_res = std::strncmp(this->data_, other.data_, n);
    if(strcmp_res != 0) {
        return strcmp_res;
    }
    if(this->len_substr_ > other.len_substr_){
        return 1;
    }
    if(this->len_substr_ < other.len_substr_){
        return -1;
    }
    return 0;
}

bool operator==(StringView lhs, StringView rhs){
    return lhs.Compare(rhs) == 0;
}
bool operator!=(StringView lhs, StringView rhs){
    return !(lhs == rhs);
}