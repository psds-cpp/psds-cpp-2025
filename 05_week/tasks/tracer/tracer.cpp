#include "tracer.hpp"

size_t Tracer::count = 0;
size_t Tracer::default_ctor = 0;
size_t Tracer::str_ctor = 0;
size_t Tracer::copy_ctor = 0;
size_t Tracer::move_ctor = 0;
size_t Tracer::copy_assign = 0;
size_t Tracer::move_assign = 0;
size_t Tracer::dtor = 0;
size_t Tracer::alive = 0;

Tracer::Tracer() : id_(++count), name_(std::format("obj_{}", id_)) {
    ++default_ctor;
    ++alive;
    std::cout << std::format("Default ctor: {} (id={})\n", name_, id_);
}

Tracer::Tracer(const std::string& name) : id_(++count), name_(name + "_" + std::to_string(id_)) {
    ++str_ctor;
    ++alive;
    std::cout << std::format("Str ctor: {} (id={})\n", name_, id_);
}

Tracer::Tracer(const Tracer& other) : id_(++count), name_(other.name_) {
    ++copy_ctor;
    ++alive;
    std::cout << std::format("Copy ctor: {} (id={}) from {}\n", name_, id_, other.id_);
}

Tracer& Tracer::operator=(const Tracer& other) {
    if (this != &other) {
        name_ = other.name_;
        ++copy_assign;
        std::cout << std::format("Copy assign: {} (id={}) <- {}\n", name_, id_, other.id_);
    }
    return *this;
}

Tracer::Tracer(Tracer&& other) noexcept : id_(++count), name_(std::move(other.name_)) {
    ++move_ctor;
    ++alive;
    std::cout << std::format("Move ctor: {} (id={}) from {}\n", name_, id_, other.id_);
}

Tracer& Tracer::operator=(Tracer&& other) noexcept {
    if (this != &other) {
        name_ = std::move(other.name_);
        ++move_assign;
        std::cout << std::format("Move assign: {} (id={}) <- {}\n", name_, id_, other.id_);
    }
    return *this;
}

Tracer::~Tracer() {
    --alive;
    ++dtor;
    std::cout << std::format("Dtor: {} (id={})\n", name_, id_);
}

void Tracer::ResetStats() {
    count = 0;
    default_ctor = 0;
    str_ctor = 0;
    copy_ctor = 0;
    move_ctor = 0;
    copy_assign = 0;
    move_assign = 0;
    dtor = 0;
    alive = 0;
    std::cout << "All stats reset to 0\n";
}
