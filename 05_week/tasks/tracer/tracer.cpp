#include <cstddef>
#include <string>

class Tracer {
public:
    // Счётчики
    static inline size_t count = 0, default_ctor = 0, str_ctor = 0, copy_ctor = 0, move_ctor = 0, copy_assign = 0, move_assign = 0, dtor = 0, alive = 0;

    // Конструкторы (объявления)
    Tracer();
    Tracer(const std::string& str);
    Tracer(const Tracer& other);
    Tracer(Tracer&& other) noexcept;
    Tracer& operator=(const Tracer& other);
    Tracer& operator=(Tracer&& other) noexcept;
    ~Tracer();

    // Методы (объявления)
    size_t Id();
    const std::string& Name() const;
    const char* Data() const;
    static void ResetStats();

private:
    std::string data;
    const size_t id;
};

// Конструкторы (реализация)
Tracer::Tracer() : id(++count) {
    data = "obj_" + std::to_string(id);
    ++alive;
    ++default_ctor;
}
Tracer::Tracer(const std::string& str) : id(++count) {
    data = str + '_' + std::to_string(id);
    ++alive;
    ++str_ctor;
}
Tracer::Tracer(const Tracer& other) : data(other.data), id(++count) {
    ++alive;
    ++copy_ctor;
}
Tracer::Tracer(Tracer&& other) noexcept : data(std::move(other.data)), id(++count) {
    other.data.clear();
    ++move_ctor;
    ++alive;
}
Tracer& Tracer::operator=(const Tracer& other) {
    if (this != &other) {
        data = other.data;
        ++copy_assign;
    }
    return *this;
}
Tracer& Tracer::operator=(Tracer&& other) noexcept {
    if (this != &other) {
        data = std::move(other.data);
        other.data.clear();
        ++move_assign;
    }
    return *this;
}
Tracer::~Tracer() {
    data.clear();
    ++dtor;
    --alive;
}

// Методы (реализации)
size_t Tracer::Id() {
    return id;
}

const std::string& Tracer::Name() const {
    return data;
}

const char* Tracer::Data() const {
    return data.c_str();
}

void Tracer::ResetStats() {
    count = 0, default_ctor = 0, str_ctor = 0, copy_ctor = 0, move_ctor = 0, copy_assign = 0, move_assign = 0, dtor = 0, alive = 0;
}