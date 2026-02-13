#include <cstddef>
#include <cstring>
#include <string>

class StringView {
public:
    inline static const size_t npos = -1;

    // Конструктор по умолчанию
    StringView() : data_(nullptr), size_(0) {}

    // Конструктор от std::string с позицией и длиной
    StringView(const std::string& str, size_t pos = 0, size_t count = npos) {
        if (pos >= str.size()) {
            data_ = nullptr;
            size_ = 0;
            return;
        }
        
        data_ = str.data() + pos;
        size_ = str.size() - pos;
        if (count != npos && count < size_) {
            size_ = count;
        }
    }

    // Конструктор от C-строки
    StringView(const char* cstr) {
        if (cstr == nullptr) {
            data_ = nullptr;
            size_ = 0;
            return;
        }
        
        data_ = cstr;
        size_ = std::strlen(cstr);
    }

    // Конструктор от C-строки и длины
    StringView(const char* cstr, size_t count) {
        if (cstr == nullptr || count == 0) {
            data_ = nullptr;
            size_ = 0;
            return;
        }
        
        data_ = cstr;
        size_ = count;
    }

    char operator[](size_t index) const {
        return data_[index];
    }

    const char* Data() const {
        return data_;
    }

    char Front() const {
        return data_[0];
    }

    char Back() const {
        return data_[size_ - 1];
    }

    size_t Size() const {
        return size_;
    }

    size_t Length() const {
        return size_;
    }

    bool Empty() const {
        return size_ == 0;
    }

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
            size_ = 0;
            data_ = nullptr;
        } else {
            size_ -= n;
        }
    }

    StringView Substr(size_t pos = 0, size_t count = npos) const {
        if (pos >= size_) {
            return StringView();
        }
        
        size_t remaining = size_ - pos;
        size_t new_size = (count != npos && count < remaining) ? count : remaining;
        
        return StringView(data_ + pos, new_size);
    }

    size_t Find(char ch, size_t pos = 0) const {
        if (pos >= size_ || Empty()) {
            return npos;
        }
        
        for (size_t i = pos; i < size_; ++i) {
            if (data_[i] == ch) {
                return i;
            }
        }
        return npos;
    }

    size_t Find(const StringView& sv, size_t pos = 0) const {
        if (sv.Empty()) {

            if (Empty()) {
                return npos;
            }
            if (pos <= size_) {
                return pos;
            }
            return npos;
        }
        
        if (Empty() || pos >= size_) {
            return npos;
        }
        
        if (sv.Size() > size_ - pos) {
            return npos;
        }
        
        for (size_t i = pos; i <= size_ - sv.Size(); ++i) {
            bool found = true;
            for (size_t j = 0; j < sv.Size(); ++j) {
                if (data_[i + j] != sv[j]) {
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

    std::string ToString() const {
        if (data_ == nullptr || size_ == 0) {
            return std::string();
        }
        return std::string(data_, size_);
    }

private:
    const char* data_;
    size_t size_;
};