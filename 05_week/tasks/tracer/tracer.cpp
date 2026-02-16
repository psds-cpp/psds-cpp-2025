#include <string>


class Tracer {
public:
    inline static size_t count = 0;
    inline static size_t default_ctor = 0;
    inline static size_t str_ctor = 0;
    inline static size_t copy_ctor = 0;
    inline static size_t move_ctor = 0;
    inline static size_t copy_assign = 0;
    inline static size_t move_assign = 0;
    inline static size_t dtor = 0;
    inline static size_t alive = 0;

    Tracer();
    Tracer(const std::string& name);
    Tracer(const Tracer& orig);
    Tracer(Tracer&& orig) noexcept;
    ~Tracer();
    Tracer& operator=(const Tracer& orig);
    Tracer& operator=(Tracer&& orig) noexcept;

    size_t Id() const noexcept;
    const std::string& Name() const noexcept;
    const char* Data() const noexcept;
    static void ResetStats() noexcept;

private:
    size_t m_id;
    std::string m_name;
};

Tracer::Tracer() :
    m_id(++count),
    m_name("obj_" + std::to_string(m_id)) {
    ++default_ctor;
    ++alive;
}

Tracer::Tracer(const std::string& name) :
    m_id(++count),
    m_name(name + '_' + std::to_string(m_id)) {
    ++str_ctor;
    ++alive;
}

Tracer::Tracer(const Tracer& orig) :
    m_id(++count),
    m_name(orig.m_name) {
    ++copy_ctor;
    ++alive;
}

Tracer::Tracer(Tracer&& orig) noexcept :
    m_id(++count),
    m_name(std::move(orig.m_name)) {
    ++move_ctor;
    ++alive;
}

Tracer::~Tracer() {
    ++dtor;
    --alive;
}

Tracer& Tracer::operator=(const Tracer& orig) {
    if (this != &orig) {
        ++copy_assign;
        m_name = orig.m_name;
    }
    return *this;
}

Tracer& Tracer::operator=(Tracer&& orig) noexcept {
    if (this != &orig) {
        ++move_assign;
        m_name = std::move(orig.m_name);
    }
    return *this;
}

size_t Tracer::Id() const noexcept {
    return m_id;
}

const std::string& Tracer::Name() const noexcept {
    return m_name;
}

const char* Tracer::Data() const noexcept {
    return m_name.data();
}

void Tracer::ResetStats() noexcept {
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