#pragma once

#include <string>
#include <iostream>
#include <format>

class Tracer {
private:
    size_t id_ = 0;
    std::string name_{};

public:
    static size_t count;
    static size_t default_ctor;
    static size_t str_ctor;
    static size_t copy_ctor;
    static size_t move_ctor;
    static size_t copy_assign;
    static size_t move_assign;
    static size_t dtor;
    static size_t alive;

    Tracer();
    Tracer(const std::string& name);
    Tracer(const Tracer& other);
    Tracer& operator=(const Tracer& other);
    Tracer(Tracer&& other) noexcept;
    Tracer& operator=(Tracer&& other) noexcept;
    ~Tracer();

    static size_t Count() { return count; }
    static size_t DefaultCtor() { return default_ctor; }
    static size_t StrCtor() { return str_ctor; }
    static size_t CopyCtor() { return copy_ctor; }
    static size_t MoveCtor() { return move_ctor; }
    static size_t CopyAssign() { return copy_assign; }
    static size_t MoveAssign() { return move_assign; }
    static size_t Dtor() { return dtor; }
    static size_t Alive() { return alive; }
    static void ResetStats();

    size_t Id() const { return id_; }
    const std::string& Name() const { return name_; }
    const char* Data() const { return name_.data(); }
};