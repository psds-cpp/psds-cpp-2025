#include <cstddef>
#include <cstring>
#include <string>

class StringView {
public:
    static inline const size_t npos = -1;

    // Конструктор по умолчанию
    StringView() : data_(nullptr), size_(0) {}

    // Конструктор от std::string с позицией и длиной
    StringView(const std::string& str, size_t pos = 0, size_t count = npos) 
        : data_(nullptr), size_(0) 
    {
        if (pos >= str.size()) {
            return;
        }
        
        data_ = str.data() + pos;
        size_ = str.size() - pos;
        if (count != npos && count < size_) {
            size_ = count;
        }
    }

    // Конструктор от временного std::string
    StringView(std::string&& str, size_t pos = 0, size_t count = npos) 
        : data_(nullptr), size_(0) 
    {
        if (pos >= str.size()) {
            return;
        }
        
        std::string* copy = new std::string(str.substr(pos, count));
        owned_data_ = copy;
        data_ = copy->data();
        size_ = copy->size();
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

    // Копирующий конструктор
    StringView(const StringView& other) 
        : data_(other.data_), size_(other.size_), owned_data_(nullptr)
    {
        // Не копируем владение - представления не владеют данными
    }

    // Оператор копирующего присваивания
    StringView& operator=(const StringView& other) {
        if (this != &other) {
            // Освобождаем владение старыми данными, если они были
            if (owned_data_) {
                delete owned_data_;
                owned_data_ = nullptr;
            }
            data_ = other.data_;
            size_ = other.size_;
        }
        return *this;
    }

    // Перемещающий конструктор
    StringView(StringView&& other) noexcept
        : data_(other.data_), size_(other.size_), owned_data_(other.owned_data_)
    {
        other.data_ = nullptr;
        other.size_ = 0;
        other.owned_data_ = nullptr;
    }

    // Перемещающее присваивание
    StringView& operator=(StringView&& other) noexcept {
        if (this != &other) {
            if (owned_data_) {
                delete owned_data_;
            }
            data_ = other.data_;
            size_ = other.size_;
            owned_data_ = other.owned_data_;
            other.data_ = nullptr;
            other.size_ = 0;
            other.owned_data_ = nullptr;
        }
        return *this;
    }

    // Деструктор
    ~StringView() {
        if (owned_data_) {
            delete owned_data_;
            owned_data_ = nullptr;
        }
    }

    // Доступ к символу по индексу
    char operator[](size_t index) const {
        return data_[index];
    }

    // Возвращает указатель на начало наблюдаемой строки
    const char* Data() const {
        return data_;
    }

    // Доступ к первому символу
    char Front() const {
        return data_[0];
    }

    // Доступ к последнему символу
    char Back() const {
        return data_[size_ - 1];
    }

    // Возвращает длину наблюдаемой строки
    size_t Size() const {
        return size_;
    }

    size_t Length() const {
        return size_;
    }

    // Проверка на пустоту
    bool Empty() const {
        return size_ == 0;
    }

    // Удаляет префикс
    void RemovePrefix(size_t n) {
        if (n >= size_) {
            data_ = nullptr;
            size_ = 0;
        } else {
            data_ += n;
            size_ -= n;
        }
    }

    // Удаляет суффикс
    void RemoveSuffix(size_t n) {
        if (n >= size_) {
            size_ = 0;
            data_ = nullptr;
        } else {
            size_ -= n;
        }
    }

    // Возвращает подстроку
    StringView Substr(size_t pos = 0, size_t count = npos) const {
        if (pos >= size_) {
            return StringView();
        }
        
        size_t remaining = size_ - pos;
        size_t new_size = (count != npos && count < remaining) ? count : remaining;
        
        return StringView(data_ + pos, new_size);
    }

    // Поиск символа
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

    // Поиск подстроки
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

    // Преобразование в std::string
    std::string ToString() const {
        if (data_ == nullptr || size_ == 0) {
            return std::string();
        }
        return std::string(data_, size_);
    }

private:
    const char* data_;
    size_t size_;
    std::string* owned_data_ = nullptr;
};