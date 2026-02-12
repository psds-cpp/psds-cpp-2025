#include <string>
#include <iostream>
#include <iomanip>

#define AddCounter(name) \
private: \
    inline static size_t name##_internal = 0; \
public: \
    inline static const auto& name = name##_internal;

#define ResetCounter(name) \
    name##_internal = 0;

#define Increment(name) \
    ++name##_internal;

#define Decrement(name) \
    --name##_internal;

#define PrintCounter(name) \
    std::cout << std::left << std::setw(12) << #name \
              << " = " << name \
              << std::endl;

class Tracer {
    AddCounter(count)
    AddCounter(default_ctor)
    AddCounter(str_ctor)
    AddCounter(copy_ctor)
    AddCounter(move_ctor)
    AddCounter(copy_assign)
    AddCounter(move_assign)
    AddCounter(dtor)
    AddCounter(alive)

public:
    Tracer();
    Tracer(const char* name);
    Tracer(const std::string& name);

    Tracer(const Tracer&);
    Tracer& operator=(const Tracer&);
    Tracer(Tracer&&) noexcept;
    Tracer& operator=(Tracer&&) noexcept;

    ~Tracer();

    static void PrintStats();
    static void ResetStats();

    int Id() const { return id_; }
    const std::string& Name() const { return name_; }
    const char* Data() const { return name_.data(); }

private:
    int id_;
    std::string name_;
};

Tracer::Tracer()
    : Tracer("obj")
{
    Increment(default_ctor)
    Decrement(str_ctor) // Чтобы не считать конструктор строки
}

Tracer::Tracer(const char* name)
    : Tracer(std::string(name))
{

}

Tracer::Tracer(const std::string& name)
    : id_(count + 1), name_(name + '_' + std::to_string(id_))
{
    Increment(count)
    Increment(str_ctor)
    Increment(alive)
}

Tracer::Tracer(const Tracer& other)
    : id_(count + 1), name_(other.name_)
{
    Increment(count) // Создает id
    Increment(copy_ctor)
    Increment(alive)
}

Tracer& Tracer::operator=(const Tracer& other)
{
    if (this != &other) {
        // Не изменяет id
        name_ = other.name_;
        Increment(copy_assign)
    }
    return *this;
}

Tracer::Tracer(Tracer&& other) noexcept
    : id_(other.id_ + 1), name_(std::move(other.name_))
{
    Increment(count) // Создает id
    Increment(move_ctor)
    Increment(alive)
}

Tracer& Tracer::operator=(Tracer&& other) noexcept
{
    if (this != &other) {
        // Не изменяет id
        name_ = std::move(other.name_);
        Increment(move_assign)
    }
    return *this;
}

Tracer::~Tracer()
{
    Increment(dtor)
    Decrement(alive)
}


void Tracer::ResetStats() {
    ResetCounter(count)
    ResetCounter(default_ctor)
    ResetCounter(str_ctor)
    ResetCounter(copy_ctor)
    ResetCounter(move_ctor)
    ResetCounter(copy_assign)
    ResetCounter(move_assign)
    ResetCounter(dtor)
    ResetCounter(alive)
}

void Tracer::PrintStats() {
    PrintCounter(count)
    PrintCounter(default_ctor)
    PrintCounter(str_ctor)
    PrintCounter(copy_ctor)
    PrintCounter(move_ctor)
    PrintCounter(copy_assign)
    PrintCounter(move_assign)
    PrintCounter(dtor)
    PrintCounter(alive)
}