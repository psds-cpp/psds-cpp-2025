#include <cstdint>
#include <stdexcept>


enum class CheckFlags : uint8_t {
    NONE = 0,
    TIME = (1 << 0),
    DATE = (1 << 1),
    USER = (1 << 2),
    CERT = (1 << 3),
    KEYS = (1 << 4),
    DEST = (1 << 5),
    ALL = TIME | DATE | USER | CERT | KEYS | DEST
};

void PrintCheckFlags(CheckFlags flags) {
    uint8_t value = static_cast<uint8_t>(flags);
    
    // Проверка на выход за диапазон (максимальное значение ALL)
    uint8_t max_value = 63; // TIME | DATE | USER | CERT | KEYS | DEST
    if (value > max_value) {
        return; // оставляем вывод пустым
    }
    
    // Начинаем вывод
    printf("[");
    
    bool first = true;
    
    // Проверяем каждый флаг
    if ((value & static_cast<uint8_t>(CheckFlags::TIME)) != 0) {
        if (!first) printf(",");
        printf("TIME");
        first = false;
    }
    
    if ((value & static_cast<uint8_t>(CheckFlags::DATE)) != 0) {
        if (!first) printf(",");
        printf("DATE");
        first = false;
    }
    
    if ((value & static_cast<uint8_t>(CheckFlags::USER)) != 0) {
        if (!first) printf(",");
        printf("USER");
        first = false;
    }
    
    if ((value & static_cast<uint8_t>(CheckFlags::CERT)) != 0) {
        if (!first) printf(",");
        printf("CERT");
        first = false;
    }
    
    if ((value & static_cast<uint8_t>(CheckFlags::KEYS)) != 0) {
        if (!first) printf(",");
        printf("KEYS");
        first = false;
    }
    
    if ((value & static_cast<uint8_t>(CheckFlags::DEST)) != 0) {
        if (!first) printf(",");
        printf("DEST");
        first = false;
    }
    
    printf("]");
}
