#include <cstdint>
#include <stdexcept>
#include <iostream>

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
    
    // Проверяем, что значение находится в допустимом диапазоне
    if (value > static_cast<uint8_t>(CheckFlags::ALL)) {
        return;  // значение вне диапазона - ничего не выводим
    }
    
    if (value == 0) {
        std::cout << "[]";  // нет флагов - выводим []
        return;
    }
    
    std::cout << "[";
    
    if (value & 1) std::cout << "TIME";
    if (value & 2) std::cout << (value & 1 ? ",DATE" : "DATE");
    if (value & 4) std::cout << (value & 3 ? ",USER" : "USER");
    if (value & 8) std::cout << (value & 7 ? ",CERT" : "CERT");
    if (value & 16) std::cout << (value & 15 ? ",KEYS" : "KEYS");
    if (value & 32) std::cout << (value & 31 ? ",DEST" : "DEST");
    
    std::cout << "]";
}
