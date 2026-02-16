#include <string>
#include <iostream>

class Tracer {
private:
    int id_;
    std::string name_;
public:
    // Статические счетчики
    inline static int count = 0;
    inline static int default_ctor = 0;
    inline static int str_ctor = 0;
    inline static int copy_ctor = 0;
    inline static int move_ctor = 0;
    inline static int copy_assign = 0;
    inline static int move_assign = 0;
    inline static int dtor = 0;
    inline static int alive = 0;

    // Конструктор по умолчанию
    Tracer() : id_(++count), name_("obj_" + std::to_string(id_)) {
        ++default_ctor;
        ++alive;
    }

    // Конструктор от строки
    Tracer(const std::string& name) : id_(++count), name_(name + "_" + std::to_string(id_)) {
        ++str_ctor;
        ++alive;
    }

    // Конструктор копирования
    Tracer(const Tracer& other) : id_(++count), name_(other.name_) {
        ++copy_ctor;
        ++alive;
    }

    // Конструктор перемещения
    Tracer(Tracer&& other) noexcept : id_(++count), name_(std::move(other.name_)) {
        ++move_ctor;
        ++alive;
    }

    // Оператор копирующего присваивания
    Tracer& operator=(const Tracer& other) {
        if (this != &other) {
            name_ = other.name_;
            ++copy_assign;
        }
        return *this;
    }

    // Оператор перемещающего присваивания
    Tracer& operator=(Tracer&& other) noexcept {
        if (this != &other) {
            name_ = std::move(other.name_);
            ++move_assign;
        }
        return *this;
    }

    // Деструктор
    ~Tracer() {
        ++dtor;
        --alive;
    }

    // Методы доступа
    int Id() const { return id_; }
    const std::string& Name() const { return name_; }
    const char* Data() const { return name_.data(); }

    // Сброс статистики
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

    // Для отладки — вывод статистики
    static void PrintStats() {
        std::cout << "count: " << count
                  << ", default_ctor: " << default_ctor
                  << ", str_ctor: " << str_ctor
                  << ", copy_ctor: " << copy_ctor
                  << ", move_ctor: " << move_ctor
                  << ", copy_assign: " << copy_assign
                  << ", move_assign: " << move_assign
                  << ", dtor: " << dtor
                  << ", alive: " << alive << "\n";
    }
};

