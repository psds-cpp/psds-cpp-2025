#include <string>

class Tracer {
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
    Tracer():
        name_("obj_" + std::to_string(++count)),
        id_(count) {
        ++default_ctor;
        ++alive;
    }
    Tracer(std::string name):
        name_(name + "_" + std::to_string(++count)), 
        id_(count) {
        ++str_ctor;
        ++alive;
    }
    Tracer(const Tracer& other):
        name_(other.name_),
        id_(++count) {
        ++copy_ctor;
        ++alive;
    }
    Tracer(Tracer&& other) noexcept :
        name_(std::move(other.name_)),
        id_(++count) {
        ++move_ctor;
        ++alive;
        other.name_ = "";
    }
    Tracer& operator=(const Tracer& other) {
        if(this != &other) {
            name_ = other.name_;
            ++copy_assign;
        }
        return *this;
    }
    Tracer& operator=(Tracer&& other) noexcept {
        if(this != &other) {
            name_ = std::move(other.name_);
            other.name_ = "";
            ++move_assign;
        }
        return *this;
    }
    ~Tracer() {
        ++dtor;
        --alive;
    }
    size_t Id() const {
        return id_;
    }
    const std::string& Name() const {
        return name_;
    }
    const char* Data() const {
        return name_.data();
    }
    static void ResetStats() {
        count = 0;
        default_ctor = 0;
        str_ctor = 0;
        copy_ctor = 0;
        move_ctor = 0;
        copy_assign = 0;
        move_assign = 0;
        dtor = 0;
        alive = 0;
    }

private:
    std::string name_;
    const size_t id_;
};

size_t Tracer::count = 0;
size_t Tracer::default_ctor = 0;
size_t Tracer::str_ctor = 0;
size_t Tracer::copy_ctor = 0;
size_t Tracer::move_ctor = 0;
size_t Tracer::copy_assign = 0;
size_t Tracer::move_assign = 0;
size_t Tracer::dtor = 0;
size_t Tracer::alive = 0;

// Вывод статистики
void PrintTracerStats() {
    std::cout << "count = " << Tracer::count << "\n"
              << "default_ctor = " << Tracer::default_ctor << "\n"
              << "str_ctor = " << Tracer::str_ctor << "\n"
              << "copy_ctor = " << Tracer::copy_ctor << "\n"
              << "move_ctor = " << Tracer::move_ctor << "\n"
              << "copy_assign = " << Tracer::copy_assign << "\n"
              << "move_assign = " << Tracer::move_assign << "\n"
              << "dtor = " << Tracer::dtor << "\n"
              << "alive = " << Tracer::alive << "\n";
}