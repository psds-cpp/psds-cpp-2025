#include <string>

class Tracer
{
private:
    std::string name;
    size_t id = 0;

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

    // конструкторы
    Tracer()
    {
        ++count;
        ++alive;
        id = alive;
        ++default_ctor;
        name = "obj_" + std::to_string(alive);
    }
    Tracer(const char *data)
    {
        ++count;
        ++alive;
        id = alive;
        ++str_ctor;
        name = data;
        name.push_back('_');
        name.append(std::to_string(id));
    }
    Tracer(const std::string &data)
    {
        ++count;
        ++alive;
        id = alive;
        ++str_ctor;
        name = data + "_" + std::to_string(alive);
    }
    Tracer(const Tracer &other)
    {
        ++count;
        ++alive;
        id = alive;
        ++copy_ctor;
        name = other.name;
        auto x = name.find('_');
        name.resize(x + 1);
        name.append(std::to_string(other.id));
    }
    Tracer(Tracer &&other) noexcept
    {
        ++move_ctor;
        ++count;
        ++alive;
        id = alive;
        name.swap(other.name);
    }
    ~Tracer()
    {
        --alive;
        ++dtor;
    }
    Tracer &operator=(Tracer &other)
    {

        if (this != &other)
        {
            ++copy_assign;
            name = other.name;
        }
        return *this;
    }
    Tracer &operator=(Tracer &&other) noexcept
    {
        if (this != &other)
        {
            ++move_assign;
            name.swap(other.name);
            other.name.clear();
        }
        return *this;
    }
    size_t Id();
    const std::string &Name();
    const char *Data();
    static void ResetStats();
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

size_t Tracer::Id()
{
    return id;
}
const std::string &Tracer::Name()
{
    return name;
}
const char *Tracer::Data()
{
    return name.data();
}
void Tracer::ResetStats()
{
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