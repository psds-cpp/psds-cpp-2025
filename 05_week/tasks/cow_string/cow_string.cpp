#include <cstring>  // для memcpy, strlen, strstr, size_t
#include <string>   // для std::string

/**
 * @brief Класс строки с семантикой copy‑on‑write (COW).
 *
 * Реализация использует подсчёт ссылок на общие данные. Все неконстантные операции,
 * которые могут изменить строку, предварительно вызывают detach(), обеспечивающий
 * уникальность данных для текущего экземпляра.
 *
 * В классе реализованы все необходимые конструкторы, операторы присваивания, деструктор,
 * а также методы для чтения и модификации строки. Особое внимание уделено
 * производительности (минимизация копирований) и корректности управления памятью.
 *
 * @note Разрешённые заголовки: <cstring> и <string>. Поэтому некоторые вспомогательные
 *       функции (std::find, std::swap) реализованы вручную.
 */
class CowString {
   private:
    // Структура, описывающая блок данных с подсчётом ссылок
    struct StringData {
        char* data;       // символьный буфер (всегда завершается '\0')
        size_t size;      // длина строки без учёта завершающего нуля
        size_t capacity;  // размер выделенной памяти (включая нуль)
        int ref_count;    // счётчик активных ссылок

        // Конструктор: выделяет буфер заданной ёмкости и копирует до len символов
        StringData(size_t cap, const char* src, size_t len)
            : size(len), capacity(cap), ref_count(1) {
            data = new char[capacity];
            if (src && len) {
                std::memcpy(data, src, len);
            }
            data[len] = '\0';
        }

        // Деструктор освобождает символьный буфер
        ~StringData() { delete[] data; }

        // Запрещаем копирование структуры (она всегда уникальна)
        StringData(const StringData&) = delete;
        StringData& operator=(const StringData&) = delete;
    };

    StringData* data_;  // указатель на управляющий блок

    // Уменьшает счётчик ссылок и, если он стал нулевым, уничтожает блок
    void release() {
        if (data_ && --data_->ref_count == 0) {
            delete data_;
        }
    }

    // Обеспечивает уникальность данных для текущего экземпляра.
    // Если объект был перемещён (data_ == nullptr), создаёт новую пустую строку.
    // Если ref_count > 1, создаётся копия блока, счётчик старого уменьшается.
    void detach() {
        if (!data_) {
            // Восстанавливаем объект после перемещения
            data_ = new StringData(1, nullptr, 0);
            return;
        }
        if (data_->ref_count > 1) {
            StringData* new_data = new StringData(data_->capacity, data_->data, data_->size);
            release();         // уменьшаем счётчик старого блока
            data_ = new_data;  // переключаемся на копию
        }
    }

    // Перераспределяет буфер под новую ёмкость (предполагается, что данные уникальны)
    void reallocate(size_t new_cap) {
        char* new_buf = new char[new_cap];
        std::memcpy(new_buf, data_->data, data_->size);
        new_buf[data_->size] = '\0';

        delete[] data_->data;
        data_->data = new_buf;
        data_->capacity = new_cap;
    }

    // Приватный конструктор для создания строки из участка памяти (используется в Substr)
    CowString(const char* s, size_t len) : data_(new StringData(len + 1, s, len)) {}

   public:
    // Специальное значение "до конца строки"
    inline static const size_t npos = -1;

    // ---------- Конструкторы / Деструктор ----------
    CowString() : data_(new StringData(1, nullptr, 0)) {}

    explicit CowString(const char* str) {
        if (!str) str = "";
        size_t len = std::strlen(str);
        data_ = new StringData(len + 1, str, len);
    }

    explicit CowString(const std::string& str)
        : data_(new StringData(str.size() + 1, str.data(), str.size())) {}  // без лишнего strlen

    CowString(const CowString& other) : data_(other.data_) {
        if (data_) ++data_->ref_count;
    }

    // Move-конструктор: noexcept, забирает указатель, другой становится nullptr
    CowString(CowString&& other) noexcept : data_(other.data_) { other.data_ = nullptr; }

    CowString& operator=(const CowString& other) {
        if (this != &other) {
            CowString temp(other);  // copy-and-swap
            swap(temp);
        }
        return *this;
    }

    CowString& operator=(CowString&& other) noexcept {
        CowString temp(std::move(other));
        swap(temp);
        return *this;
    }

    ~CowString() { release(); }

    // ---------- Наблюдающие методы (не вызывают копирования) ----------
    size_t Size() const { return data_ ? data_->size : 0; }
    const char* ToCstr() const { return data_ ? data_->data : ""; }
    std::string ToString() const {
        if (!data_) return std::string();
        return std::string(data_->data, data_->size);
    }
    operator const char*() const { return ToCstr(); }
    bool Empty() const { return Size() == 0; }

    // Чтение по индексу (const‑версия) – без проверки границ, как в тестах
    const char& operator[](size_t index) const { return data_->data[index]; }

    // Запись по индексу – требует копирования перед записью
    char& operator[](size_t index) {
        detach();  // гарантирует data_ != nullptr
        return data_->data[index];
    }

    // Модифицирующие методы
    CowString& Append(const char* str) {
        if (!str) return *this;
        size_t add_len = std::strlen(str);
        if (add_len == 0) return *this;

        detach();

        size_t new_size = data_->size + add_len;
        size_t needed = new_size + 1;
        if (needed > data_->capacity) {
            size_t new_cap = data_->capacity * 2;
            if (new_cap < needed) new_cap = needed;
            reallocate(new_cap);
        }

        std::memcpy(data_->data + data_->size, str, add_len);
        data_->size = new_size;
        data_->data[new_size] = '\0';
        return *this;
    }

    CowString& Append(const std::string& str) { return Append(str.c_str()); }

    void Clear() {
        detach();
        data_->size = 0;
        data_->data[0] = '\0';
    }

    CowString Substr(size_t pos = 0, size_t count = npos) const {
        if (!data_ || pos >= data_->size) {
            return CowString();
        }
        size_t start = pos;
        size_t max_len = data_->size - pos;
        size_t len = (count == npos || count > max_len) ? max_len : count;
        return CowString(data_->data + start, len);
    }

    // ---------- Поиск ----------
    size_t Find(char c) const {
        if (!data_) return npos;
        for (size_t i = 0; i < data_->size; ++i) {
            if (data_->data[i] == c) return i;
        }
        return npos;
    }

    size_t Find(const char* substr) const {
        if (!data_ || !substr) return npos;
        if (!*substr) return 0;  // пустая подстрока всегда в начале
        const char* found = std::strstr(data_->data, substr);
        return found ? static_cast<size_t>(found - data_->data) : npos;
    }

    // ---------- Дополнительные методы, расширяющие интерфейс ----------
    size_t Capacity() const { return data_ ? data_->capacity - 1 : 0; }
    const char* Data() const { return ToCstr(); }

    // Итераторы для поддержки range-based for
    const char* begin() const { return ToCstr(); }
    const char* end() const { return ToCstr() + Size(); }

    // Операторы сравнения
    friend bool operator==(const CowString& lhs, const CowString& rhs) {
        if (lhs.Size() != rhs.Size()) return false;
        return std::memcmp(lhs.ToCstr(), rhs.ToCstr(), lhs.Size()) == 0;
    }
    friend bool operator!=(const CowString& lhs, const CowString& rhs) { return !(lhs == rhs); }
    friend bool operator==(const CowString& lhs, const char* rhs) {
        if (!rhs) rhs = "";
        size_t rhs_len = std::strlen(rhs);
        if (lhs.Size() != rhs_len) return false;
        return std::memcmp(lhs.ToCstr(), rhs, rhs_len) == 0;
    }
    friend bool operator!=(const CowString& lhs, const char* rhs) { return !(lhs == rhs); }

    void swap(CowString& other) {
        StringData* tmp = data_;
        data_ = other.data_;
        other.data_ = tmp;
    }
};