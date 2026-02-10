#include <string>


class Tracer {
private:
    int id_;    
    std::string name_;


public:
    // Переменные - счётчики
    inline static int count = 0;
    inline static int default_ctor = 0;
    inline static int str_ctor = 0;
    inline static int copy_ctor = 0;
    inline static int move_ctor = 0;
    inline static int copy_assign = 0;
    inline static int move_assign = 0;
    inline static int dtor = 0;
    inline static int alive = 0;

    // Конструкторы
    Tracer() : id_(++count),  name_("obj_" + std::to_string(id_)) {
        ++default_ctor;
        ++alive;
    }

    explicit Tracer(const std::string& st) : id_(++count),  name_(st + '_' + std::to_string(id_)) {
        ++str_ctor;
        ++alive;
    }

    Tracer(const Tracer& other) : id_(++count), name_(other.name_) {
        ++copy_ctor;
        ++alive;
    }

    Tracer(Tracer&& other) noexcept : id_(++count), name_(std::move(other.name_)) {
        ++move_ctor;
        ++alive;
    }

    Tracer& operator=(const Tracer& other) {
        if (this != &other) {
            this->name_ = other.name_;
            ++copy_assign;
        }
        return *this;
    }

    Tracer& operator=(Tracer&& other) noexcept {
        if (this != &other) {
            this->name_ = std::move(other.name_);
            ++move_assign;
        }
        return *this;
    }

    // Деструктор
    ~Tracer() {
        ++dtor;
        --alive;
    }

    // Методы

    int Id() const {
        return id_;
    }

    const std::string& Name() const {
        return name_;
    }

    const char* Data() const {
        return name_.c_str();
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
};