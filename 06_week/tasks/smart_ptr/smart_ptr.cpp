#include <string>


struct  ControlBlock
{
    unsigned int strong_count = 0;
    unsigned int weak_count = 0;
};

class SharedPtr {
public:
    // Конструкторы и деструктор
    explicit SharedPtr(std::string* data = nullptr);
    SharedPtr(std::string* data, ControlBlock* cb);
    SharedPtr(const SharedPtr& other);
    SharedPtr(SharedPtr&& other) noexcept;
    ~SharedPtr();

    // Операторы
    SharedPtr& operator=(const SharedPtr& other);
    SharedPtr& operator=(SharedPtr&& other) noexcept;
    explicit operator bool() const noexcept;
    std::string& operator*() const;
    std::string* operator->() const;

    // Методы
    std::string* Get();
    const std::string* Get() const;
    void Reset(std::string* data = nullptr);
    void Swap(SharedPtr& other);
    unsigned int UseCount() const;

    // Дружественные функции
    friend ControlBlock* GetControlBlock(const SharedPtr& obj);

private:
    std::string* data_;
    ControlBlock* cb_;

    // Приватные методы
    void DeleteData();
};

class WeakPtr {
public:
    // Конструкторы и деструктор
    WeakPtr();
    WeakPtr(const SharedPtr& other);
    WeakPtr(const WeakPtr& other);
    WeakPtr(WeakPtr&& other) noexcept;
    ~WeakPtr();

    // Операторы
    WeakPtr& operator=(const SharedPtr& other);
    WeakPtr& operator=(const WeakPtr& other);
    WeakPtr& operator=(WeakPtr&& other) noexcept;
    const std::string& operator*() const;
    const std::string* operator->() const;

    // Методы
    const std::string* Get() const;
    void Reset();
    void Swap(WeakPtr& other);
    unsigned int UseCount() const;
    bool Expired() const;
    SharedPtr Lock() const;

    // Дружественные функции
    friend ControlBlock* GetControlBlock(const WeakPtr& obj);

private:
    const std::string* data_;
    ControlBlock* cb_;

    // Приватные методы
    void DeleteData();
};

// SharedPtr
// Приватные методы
void SharedPtr::DeleteData() {
    if (cb_) {
        if (--cb_->strong_count == 0) { 
            delete data_; 
            if (cb_->weak_count == 0) delete cb_;
        }
    }
}

// Конструкторы и деструктор
SharedPtr::SharedPtr(std::string* data) : data_(data), cb_((data) ? new ControlBlock() : nullptr) {
    if (cb_) ++cb_->strong_count;
}

SharedPtr::SharedPtr(std::string* data, ControlBlock* cb) : data_((data && cb) ? data : nullptr), cb_((data && cb) ? cb : nullptr) {
    if (data && cb) ++cb_->strong_count;
}

SharedPtr::SharedPtr(const SharedPtr& other) : data_(other.data_), cb_(other.cb_) {
    if (cb_) ++cb_->strong_count;
}

SharedPtr::SharedPtr(SharedPtr&& other) noexcept : data_(other.data_), cb_(other.cb_) {
    other.data_ = nullptr;
    other.cb_ = nullptr;
}

SharedPtr::~SharedPtr() {
    DeleteData();
}

// Операторы
SharedPtr& SharedPtr::operator=(const SharedPtr& other) {
    if (this != &other) {
        DeleteData();
        std::tie(data_, cb_) = std::tie(other.data_, other.cb_);
        if (cb_) ++cb_->strong_count;
    }
    return *this;
}

SharedPtr& SharedPtr::operator=(SharedPtr&& other) noexcept {
    if (this != &other) {
        DeleteData();
        std::tie(data_, cb_) = std::tie(other.data_, other.cb_);
        std::tie(other.data_, other.cb_) = std::make_tuple(nullptr, nullptr);
    }
    return *this;
}

SharedPtr::operator bool() const noexcept {
    return data_;
}

std::string& SharedPtr::operator*() const { return *data_; }

std::string* SharedPtr::operator->() const { return data_; }

// Методы
std::string* SharedPtr::Get() { return data_; }

const std::string* SharedPtr::Get() const { return data_; }

void SharedPtr::Reset(std::string* data) {
    if (data_ != data) {
        DeleteData();
        data_ = data;
        cb_ = (data) ? new ControlBlock() : nullptr;
        if (cb_) ++cb_->strong_count;
    }
}

void SharedPtr::Swap(SharedPtr& other) {
    std::swap(data_, other.data_);
    std::swap(cb_, other.cb_);
}

unsigned int SharedPtr::UseCount() const {
    return (cb_) ? cb_->strong_count : 0;
}

// WeakPtr
// Приватные методы
void WeakPtr::DeleteData() {
    if (cb_) {
        if (--cb_->weak_count == 0 && cb_->strong_count == 0) {
            delete cb_;
        }
    }
}

// Конструкторы и деструктор
WeakPtr::WeakPtr() : data_(nullptr), cb_(nullptr) {}

WeakPtr::WeakPtr(const SharedPtr& other) : data_(other.Get()), cb_(GetControlBlock(other)) {
    if (cb_) ++cb_->weak_count;
}

WeakPtr::WeakPtr(const WeakPtr& other) : data_(other.data_), cb_(other.cb_) {
    if (cb_) ++cb_->weak_count;
}

WeakPtr::WeakPtr(WeakPtr&& other) noexcept : data_(other.data_), cb_(other.cb_) {
    other.data_ = nullptr;
    other.cb_ = nullptr;
}

WeakPtr::~WeakPtr() {
    DeleteData();
}

// Операторы
WeakPtr& WeakPtr::operator=(const SharedPtr& other) {
    DeleteData();
    data_ = other.Get(); 
    cb_ = GetControlBlock(other);
    if (cb_) ++cb_->weak_count;
    return *this;
}

WeakPtr& WeakPtr::operator=(const WeakPtr& other) {
    if (this != &other) {
        DeleteData();
        std::tie(data_, cb_) = std::tie(other.data_, other.cb_);
        if (cb_) ++cb_->weak_count;
    }
    return *this;
}

WeakPtr& WeakPtr::operator=(WeakPtr&& other) noexcept {
    if (this != &other) {
        DeleteData();
        std::tie(data_, cb_) = std::tie(other.data_, other.cb_);
        std::tie(other.data_, other.cb_) = std::make_tuple(nullptr, nullptr);
    }
    return *this;
}

const std::string& WeakPtr::operator*() const {
    return *data_;
}

const std::string* WeakPtr::operator->() const {
    return data_;
}

// Методы
const std::string* WeakPtr::Get() const {
    return data_;
}

void WeakPtr::Reset() {
    DeleteData();
    data_ = nullptr;
    cb_ = nullptr;
}

void WeakPtr::Swap(WeakPtr& other) {
    std::swap(data_, other.data_);
    std::swap(cb_, other.cb_);
}

unsigned int WeakPtr::UseCount() const {
    return (cb_) ? cb_->strong_count : 0;
}

bool WeakPtr::Expired() const {
    return !cb_ || cb_->strong_count == 0;
}

SharedPtr WeakPtr::Lock() const {
    if (Expired()) {
        return SharedPtr();
    }
    return SharedPtr(const_cast<std::string*>(data_), cb_);
}

// Внешние функции
SharedPtr MakeShared(const std::string& str) {
    return SharedPtr(new std::string(str));
}

SharedPtr MakeShared(std::string&& str) {
    return SharedPtr(new std::string(std::move(str)));
}

void Swap(SharedPtr& ptr_1, SharedPtr& ptr_2) {
    ptr_1.Swap(ptr_2);
}

void Swap(WeakPtr& ptr_1, WeakPtr& ptr_2) {
    ptr_1.Swap(ptr_2);
}

// Дружественные функции
ControlBlock* GetControlBlock(const SharedPtr& obj) {
    return obj.cb_;
}

ControlBlock* GetControlBlock(const WeakPtr& obj) {
    return obj.cb_;
}
