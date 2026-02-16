#include <cstring>
#include <string>

class StringView
{
public:
    inline static const size_t npos = static_cast<size_t>(-1);

private:
    const char *data_;
    size_t size_;

public:
    StringView() : data_(nullptr), size_(0) {}
    StringView(const std::string &str, size_t pos = 0, size_t len = npos)
    {
        if (pos >= str.size())
        {
            data_ = nullptr;
            size_ = 0;
            return;
        }

        size_t real_len = (len == npos || pos + len > str.size()) ? str.size() - pos : len;

        data_ = str.data() + pos;
        size_ = real_len;
    }
    StringView(const char *str) : data_(str), size_(str ? std::strlen(str) : 0) {}
    StringView(const char *str, size_t len) : data_(str), size_(str ? len : 0) {}
    const char &operator[](size_t index) const { return data_[index]; }
    const char *Data() const { return data_; }
    const char &Front() const { return data_[0]; }
    const char &Back() const { return data_[size_ - 1]; }
    size_t Size() const { return size_; }
    size_t Length() const { return size_; }
    bool Empty() const { return size_ == 0; }
    void RemovePrefix(size_t n)
    {
        if (n > size_)
            n = size_;
        data_ += n;
        size_ -= n;
    }
    void RemoveSuffix(size_t n)
    {
        if (n > size_)
            n = size_;
        size_ -= n;
    }
    StringView Substr(size_t pos, size_t len = npos) const
    {
        if (pos >= size_)
            return StringView();

        size_t real_len = (len == npos || pos + len > size_) ? size_ - pos : len;
        return StringView(data_ + pos, real_len);
    }
    size_t Find(char ch, size_t pos = 0) const
    {
        if (pos >= size_)
            return npos;

        for (size_t i = pos; i < size_; ++i)
        {
            if (data_[i] == ch)
                return i;
        }
        return npos;
    }
    size_t Find(StringView sv, size_t pos = 0) const
    {
        if (sv.size_ == 0)
            return (pos <= size_) ? pos : npos;
        if (sv.size_ > size_ || pos >= size_)
            return npos;

        for (size_t i = pos; i + sv.size_ <= size_; ++i)
        {
            if (std::memcmp(data_ + i, sv.data_, sv.size_) == 0)
                return i;
        }
        return npos;
    }
    std::string ToString() const { return std::string(data_, size_); }
};