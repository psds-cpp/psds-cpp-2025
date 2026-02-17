#include <cstring>
#include <string>
#include <stdexcept>
#include <algorithm>

class StringView {
public:
    StringView() : data_(nullptr), size_(0) {}

    StringView(const std::string& str, size_t pos = 0, size_t len = std::string::npos) {
        if (pos > str.size()) {
            data_ = nullptr;
            size_ = 0;
        } else {
            data_ = str.data() + pos;
            size_ = std::min(len, str.size() - pos);
        }
    }

    StringView(const char* str) {
        data_ = str;
        size_ = str ? std::strlen(str) : 0;
    }

    StringView(const char* str, size_t len) {
        data_ = str;
        size_ = str ? len : 0;
    }

    StringView(const StringView& other) = default;

    char operator[](size_t index) const {
        if (index >= size_) throw std::out_of_range("Index out of range");
        return data_[index];
    }

    const char* Data() const { return data_; }

    char Front() const {
        if (Empty()) throw std::out_of_range("StringView is empty");
        return data_[0];
    }

    char Back() const {
        if (Empty()) throw std::out_of_range("StringView is empty");
        return data_[size_ - 1];
    }

    size_t Size() const { return size_; }
    size_t Length() const { return size_; }

    bool Empty() const { return size_ == 0; }

    void RemovePrefix(size_t n) {
        if (n >= size_) {
            data_ = nullptr;
            size_ = 0;
        } else {
            data_ += n;
            size_ -= n;
        }
    }

    void RemoveSuffix(size_t n) {
        if (n >= size_) {
            data_ = nullptr;
            size_ = 0;
        } else {
            size_ -= n;
        }
    }

    StringView Substr(size_t pos = 0, size_t len = std::string::npos) const {
        if (pos > size_) return StringView(nullptr, 0);
        return StringView(data_ + pos, std::min(len, size_ - pos));
    }

    size_t Find(char ch, size_t pos = 0) const {
        if (pos >= size_) return npos;
        for (size_t i = pos; i < size_; ++i) {
            if (data_[i] == ch) return i;
        }
        return npos;
    }

    size_t Find(const StringView& sv, size_t pos = 0) const {
        if (sv.size_ == 0) return pos <= size_ ? pos : npos;
        if (sv.size_ > size_ || pos > size_ - sv.size_) return npos;

        for (size_t i = pos; i <= size_ - sv.size_; ++i) {
            if (std::memcmp(data_ + i, sv.data_, sv.size_) == 0)
                return i;
        }
        return npos;
    }

    std::string ToString() const {
        return data_ ? std::string(data_, size_) : std::string();
    }

    inline static const size_t npos = static_cast<size_t>(-1);

private:
    const char* data_ = nullptr;
    size_t size_ = 0;
};

