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

    Tracer() {
        ++count;
        ++default_ctor;
        ++alive;
        id_ = count;
        name_ = "obj_" + std::to_string(id_);
    }

    Tracer(const std::string& objName) {
        ++count;
        ++str_ctor;
        ++alive;
        id_ = count;
        name_ = objName + '_' + std::to_string(id_);
    }

    Tracer(const Tracer& other) {
        ++count;
        ++copy_ctor;
        ++alive;
        id_ = count;
        name_ = other.name_;
    }

    Tracer(Tracer&& other) noexcept {
        ++count;
        ++move_ctor;
        ++alive;
        id_ = count;
        name_ = std::move(other.name_);
    }

    Tracer& operator=(const Tracer& other) {
        if (other.id_ == id_ ) {
            return *this;
        }

        ++copy_assign;
        name_ = other.name_;
        return *this;
    }

    Tracer& operator=(Tracer&& other) noexcept {
        if (other.id_ == id_) {
            return *this;
        }

        ++move_assign;
        name_ = std::move(other.name_);
        return *this;
    }

    ~Tracer() {
        ++dtor;
        --alive;
    }

    size_t Id();
    const std::string& Name() const;
    const char* Data() const;
    static void ResetStats(); 
    
private:
    size_t id_;
    std::string name_;
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

size_t Tracer::Id() {
    return id_;
}

const std::string& Tracer::Name() const {
    return name_;
}

const char* Tracer::Data() const {
    return name_.data();
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
}
