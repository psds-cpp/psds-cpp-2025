#include <string>
#include <utility>

class Tracer {
public:
    Tracer();
    ~Tracer();
    Tracer(const std::string& name);
    Tracer(const Tracer& other);
    Tracer(Tracer&& other) noexcept;
    int Id() const;
    const std::string& Name() const;
    char* Data();
    static void ResetStats();
    Tracer& operator=(const Tracer& other);
    Tracer& operator=(Tracer&& other) noexcept;
    inline static int count = 0;
    inline static int default_ctor = 0;
    inline static int str_ctor = 0;
    inline static int copy_ctor = 0;
    inline static int move_ctor = 0;
    inline static int copy_assign = 0;
    inline static int move_assign = 0;
    inline static int dtor = 0;
    inline static int alive = 0;
private:
    int m_id = 0;
    std::string m_name = "";
};

Tracer::Tracer() : m_id(++count), m_name("obj_" + std::to_string(m_id)) {
    ++alive;
    ++default_ctor;
}

Tracer::~Tracer() {
    --alive;
    ++dtor;
}

Tracer::Tracer(const std::string &name) : m_id(++count), m_name(name + "_" + std::to_string(m_id)) {
    ++alive;
    ++str_ctor;
}

Tracer::Tracer(const Tracer &other) : m_id(++count), m_name(other.m_name) {
    ++alive;
    ++copy_ctor;
}

Tracer::Tracer(Tracer &&other) noexcept : m_id(++count), m_name(std::move(other.m_name)) {
    ++alive;
    ++move_ctor;
}

int Tracer::Id() const {
    return m_id;
}

const std::string& Tracer::Name() const {
    return m_name;
}

char* Tracer::Data() {
    return m_name.data();
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

Tracer& Tracer::operator=(const Tracer &other) {
    if (this == &other) { return *this; }
    ++copy_assign;
    m_name = other.m_name;
    return *this;
}

Tracer& Tracer::operator=(Tracer &&other) noexcept {
    if (this == &other) { return *this; }
    ++move_assign;
    m_name = std::move(other.m_name);
    return *this;
}
