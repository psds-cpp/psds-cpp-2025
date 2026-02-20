#include <memory>
#include <string>
#include <utility>

/// Контрольный блок для SharedPtr и WeakPtr
struct ControlBlock { 
    std::string* data_ptr = nullptr;

    size_t strong_count = 0;    ///< Количество SharedPtr, управляющих объектом
    size_t weak_count = 0;      ///< Количество WeakPtr, ссылающихся на объект (не включая SharedPtr)
};

/// Умный указатель с разделяемым владением
class SharedPtr {
    friend class WeakPtr;

public:
    SharedPtr(std::string* ptr = nullptr);

    SharedPtr(const SharedPtr& other);
    SharedPtr& operator=(const SharedPtr& other);

    SharedPtr(SharedPtr&& other) noexcept;
    SharedPtr& operator=(SharedPtr&& other) noexcept;

    ~SharedPtr() noexcept;

    // Фабричные функции для SharedPtr
    friend SharedPtr MakeShared(std::string&  value);
    friend SharedPtr MakeShared(std::string&& value);

    std::string* Get() noexcept;
    const std::string* Get() const noexcept;

    void Reset(std::string* ptr = nullptr) noexcept;
    void Swap(SharedPtr& other);
    size_t UseCount() const noexcept;

    operator bool() const noexcept { return Get() != nullptr; }
    std::string& operator*() noexcept { return *Get(); }
    const std::string& operator*() const noexcept { return *Get(); }
    std::string* operator->() noexcept { return Get(); }
    const std::string* operator->() const noexcept { return Get(); }

private:
    SharedPtr(ControlBlock* ctrl);

private:
    ControlBlock* ctrl_;
};

SharedPtr MakeShared(std::string& value)
{
    // Копирование принимаемого объекта
    return SharedPtr(new ControlBlock{new std::string(value)});
}
SharedPtr MakeShared(std::string&& value)
{
    // Перемещение принимаемого объекта
    return SharedPtr(new ControlBlock{new std::string(std::move(value))});
}

void Swap(SharedPtr& lhs, SharedPtr& rhs)
{
    lhs.Swap(rhs);
}


/// Умный указатель, не владеющий объектом, но способный наблюдать за ним
class WeakPtr {
public:
    WeakPtr() = default;
    WeakPtr(const SharedPtr& shared);
    
    WeakPtr(const WeakPtr& other);
    WeakPtr& operator=(const WeakPtr& other);

    WeakPtr(WeakPtr&& other) noexcept;
    WeakPtr& operator=(WeakPtr&& other) noexcept;

    ~WeakPtr() noexcept;

    void Reset() noexcept;
    SharedPtr Lock() const;
    void Swap(WeakPtr& other);
    size_t UseCount() const noexcept;
    bool Expired() const noexcept;

private:
    ControlBlock* ctrl_ = nullptr;
};

void Swap(WeakPtr& lhs, WeakPtr& rhs)
{
    lhs.Swap(rhs);
}

// ---------------------------------------------------------------------------
// Реализация SharedPtr
// ---------------------------------------------------------------------------

SharedPtr::SharedPtr(ControlBlock* ctrl) 
    : ctrl_(ctrl) 
{
    if (ctrl_)
        ++ctrl_->strong_count;
}

SharedPtr::SharedPtr(std::string* ptr) 
    : ctrl_(ptr ? new ControlBlock{ptr, 1} : nullptr)
{

}

SharedPtr::SharedPtr(const SharedPtr& other) 
    : ctrl_(other.ctrl_)
{
    if (ctrl_)
        ++ctrl_->strong_count;
}
SharedPtr& SharedPtr::operator=(const SharedPtr& other) 
{
    if (this != std::addressof(other)) {
        Reset();

        ctrl_ = other.ctrl_;
        if (ctrl_)
            ++ctrl_->strong_count;
    }
    return *this;
}

SharedPtr::SharedPtr(SharedPtr&& other) noexcept
    : ctrl_(std::exchange(other.ctrl_, nullptr))
{

}

SharedPtr& SharedPtr::operator=(SharedPtr&& other) noexcept
{
    if (this != std::addressof(other)) {
        Reset();  
        ctrl_ = std::exchange(other.ctrl_, nullptr);
    }
    return *this;
}

SharedPtr::~SharedPtr() noexcept 
{
    Reset();
}

std::string* SharedPtr::Get() noexcept
{
    return ctrl_ ? ctrl_->data_ptr : nullptr;
}
const std::string* SharedPtr::Get() const noexcept
{
    return ctrl_ ? ctrl_->data_ptr : nullptr;
}

void SharedPtr::Reset(std::string* ptr) noexcept
{
    if (ctrl_) {
        // Если "сильный" счётчик обнуляется, удаляем управляемый объект
        if (--ctrl_->strong_count == 0) {
            if (ctrl_->data_ptr) {
                delete ctrl_->data_ptr;
                ctrl_->data_ptr = nullptr;
            }
            // Если оба счётчика обнуляются, удаляем контрольный блок
            if (ctrl_->weak_count == 0)
                delete ctrl_;
        }
        ctrl_ = nullptr;
    }

    if (ptr)
        ctrl_ = new ControlBlock{ptr, 1};
}

void SharedPtr::Swap(SharedPtr& other)
{
    std::swap(ctrl_, other.ctrl_);
}

size_t SharedPtr::UseCount() const noexcept
{
    return ctrl_ ? ctrl_->strong_count : 0;
}

// ---------------------------------------------------------------------------
// Реализация WeakPtr
// ---------------------------------------------------------------------------

WeakPtr::WeakPtr(const SharedPtr& shared) 
    : ctrl_(shared.ctrl_)
{
    if (ctrl_)
        ++ctrl_->weak_count;
}

WeakPtr::WeakPtr(const WeakPtr& other) 
    : ctrl_(other.ctrl_)
{
    if (ctrl_)
        ++ctrl_->weak_count;
}
WeakPtr& WeakPtr::operator=(const WeakPtr& other) 
{
    if (this != std::addressof(other)) {
        Reset();

        ctrl_ = other.ctrl_;
        if (ctrl_)
            ++ctrl_->weak_count;
    }
    return *this;
}

WeakPtr::WeakPtr(WeakPtr&& other) noexcept
    : ctrl_(std::exchange(other.ctrl_, nullptr))
{

}

WeakPtr& WeakPtr::operator=(WeakPtr&& other) noexcept
{
    if (this != std::addressof(other)) {
        Reset();  
        ctrl_ = std::exchange(other.ctrl_, nullptr);
    }
    return *this;
}

WeakPtr::~WeakPtr() noexcept
{
    Reset();
}

void WeakPtr::Reset() noexcept
{
    if (ctrl_) {
        // Если "слабый" счётчик обнуляется и нет "сильных" указателей, удаляем контрольный блок
        if (--ctrl_->weak_count == 0 && ctrl_->strong_count == 0)
            delete ctrl_;
        ctrl_ = nullptr;
    }
}

void WeakPtr::Swap(WeakPtr& other)
{
    std::swap(ctrl_, other.ctrl_);
}

size_t WeakPtr::UseCount() const noexcept
{
    // Возвращает количество "сильных" указателей, управляющих объектом
    return ctrl_ ? ctrl_->strong_count : 0;
}

bool WeakPtr::Expired() const noexcept
{
    return !ctrl_ || ctrl_->strong_count == 0;
}

SharedPtr WeakPtr::Lock() const
{
    if (Expired())
        return SharedPtr();

    return SharedPtr(ctrl_);
}