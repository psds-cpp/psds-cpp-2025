#include <memory>
#include <string>
#include <utility>

class UniquePtr {
public:
    UniquePtr() = default;
    UniquePtr(std::string* ptr);

    // Не допускает копирования, только перемещение
    UniquePtr(const UniquePtr& other) = delete;
    UniquePtr& operator=(const UniquePtr& other) = delete;

    UniquePtr(UniquePtr&& other) noexcept;
    UniquePtr& operator=(UniquePtr&& other) noexcept;

    ~UniquePtr() noexcept;

    friend UniquePtr MakeUnique(std::string&  value);
    friend UniquePtr MakeUnique(std::string&& value);

    std::string* Get() noexcept;
    const std::string* Get() const noexcept;

    std::string* Release() noexcept;
    void Reset(std::string* ptr = nullptr) noexcept;
    void Swap(UniquePtr& other);
    
    operator bool() const noexcept { return Get() != nullptr; }
    std::string& operator*() noexcept { return *Get(); }
    const std::string& operator*() const noexcept { return *Get(); }
    std::string* operator->() noexcept { return Get(); }
    const std::string* operator->() const noexcept { return Get(); }

private:
    std::string* data_ptr_ = nullptr;
};

template<typename... Args> 
UniquePtr MakeUnique(Args&&... args) 
    requires std::constructible_from<std::string, Args...> 
{ 
    return UniquePtr(new std::string(std::forward<Args>(args)...)); 
}

void Swap(UniquePtr& lhs, UniquePtr& rhs)
{
    lhs.Swap(rhs);
}

// ---------------------------------------------------------------------------
// Реализация UniquePtr
// ---------------------------------------------------------------------------

UniquePtr::UniquePtr(std::string* ptr) 
    : data_ptr_(ptr) 
{

}

UniquePtr::UniquePtr(UniquePtr&& other) noexcept
    : data_ptr_(std::exchange(other.data_ptr_, nullptr))
{

}

UniquePtr& UniquePtr::operator=(UniquePtr&& other) noexcept
{
    if (this != std::addressof(other)) {
        Reset();  
        data_ptr_ = std::exchange(other.data_ptr_, nullptr);
    }
    return *this;
}

UniquePtr::~UniquePtr()  noexcept
{
    if (data_ptr_)
        delete data_ptr_;
}

std::string* UniquePtr::Get() noexcept
{
    return data_ptr_;
}

const std::string* UniquePtr::Get() const noexcept
{
    return data_ptr_;
}

void UniquePtr::Reset(std::string* ptr) noexcept
{
    if (data_ptr_)
        delete data_ptr_;
    data_ptr_ = ptr;
}

std::string* UniquePtr::Release() noexcept
{
    auto* const temp = data_ptr_;
    data_ptr_ = nullptr;
    return temp;
}

void UniquePtr::Swap(UniquePtr& other)
{
    std::swap(data_ptr_, other.data_ptr_);
}


