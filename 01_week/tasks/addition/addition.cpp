#include <cstdint> // заголовочный файл с целочисленными типами фиксированного размера
#include <stdexcept> // из этого мы ничего не используем

// функция принимает две перменных типа int и возвращает число типа int64_t
int64_t Addition(int a, int b) {
<<<<<<< HEAD
    throw std::runtime_error{"Not implemented"};
    // для первого коммита 
=======
// Чтобы сложение выполнялось в int64_t, приводим a и b к этому типу
// static_cast<новый тип>(переменная)
    return static_cast<int64_t>(a) + static_cast<int64_t>(b); 
>>>>>>> 612865a (addition)
}