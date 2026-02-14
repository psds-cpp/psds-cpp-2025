#include <cstring>
#include <string>

class StringView {
public:
    StringView() = default;
    StringView(const std::string& str, size_t begin, size_t len_substr);
    StringView(const std::string&& str, size_t begin, size_t len_substr);
    StringView(const char* cstr, size_t len_substr);
    const char& operator[](size_t index) const;
    const char* Data() const { return data_; }
    const char& Front() const { return *(data_); }
    const char& Back() const { return *(data_ + length_ - 1); }
    size_t Size() const { return length_; }
    size_t Length() const { return length_; }
    bool Empty() const { return length_ == 0; }
    void RemovePrefix(size_t count);
    void RemoveSuffix(size_t count);
    StringView Substr(size_t begin = 0, size_t len = npos) const;
    size_t Find(StringView strview, size_t pos) const;
    size_t Find(char c, size_t pos) const;
    std::string ToString() const;
    int Compare(StringView other) const;
    static const size_t npos;

private:
    const char* data_ = nullptr;
    size_t length_ = 0;
};

const size_t StringView::npos = -1;

StringView::StringView(const std::string& str, size_t begin = 0, size_t len_substr = npos) {
    if(begin <= str.size()){
        data_ = str.c_str() + begin;
        length_ = std::min(str.size() - begin, len_substr);
    }
}

StringView::StringView(const std::string&& str, size_t begin = 0, size_t len_substr = npos) {
    if(begin <= str.size()){
        data_ = str.c_str() + begin;
        length_ = std::min(str.size() - begin, len_substr);
    }
}

StringView::StringView(const char* cstr, size_t len_substr = npos) {
    if(cstr && len_substr > 0) {
        data_ = cstr;
        length_ = std::min(len_substr, std::strlen(cstr));
    }
}

const char& StringView::operator[](size_t index) const {
    return index > length_ ? *(data_ + length_) : *(data_ + index);
}

StringView StringView::Substr(size_t begin, size_t len) const {
    return begin < length_ ? StringView(data_ + begin, len) : StringView(data_, 0);
}
size_t StringView::Find(StringView strview, size_t pos = 0) const {
    pos = std::min(pos, length_);
    if (Empty() || strview.Size() > length_ - pos) {
        return npos;
    }
    if (strview.Empty()) {
        return 0;
    }

    for (size_t i = pos; i <= length_ - strview.Size(); ++i) {
        if (std::memcmp(data_ + i, strview.Data(), strview.Size()) == 0) {
            return i;
        }
    }
    return npos;
}
size_t StringView::Find(char c, size_t pos = 0) const {
    if (Empty()) {
        return npos;
    }

    pos = std::min(pos, length_);
    for (size_t i = pos; i <= length_; ++i) {
        if (*(data_ + i) == c) {
            return i;
        }
    }
    return npos;
};
std::string StringView::ToString() const {
    return std::string(data_, length_);
}

int StringView::Compare(StringView other) const {
    size_t n = std::min(this->length_, other.length_);
    int strcmp_res = std::strncmp(this->data_, other.data_, n);
    if(strcmp_res != 0) {
        return strcmp_res;
    }
    if(this->length_ > other.length_){
        return 1;
    }
    if(this->length_ < other.length_){
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

void StringView::RemovePrefix(size_t count) {
    data_ += count > length_ ? length_ : count;
    length_ -= count > length_ ? length_ : count;
}

void StringView::RemoveSuffix(size_t count) {
    length_ -= count > length_ ? length_ : count;
}