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
    
    if (value > static_cast<uint8_t>(CheckFlags::ALL)) {
        return;
    }
    
    // Обработка специального случая NONE
    if (flags == CheckFlags::NONE) {
        std::cout << "[]";
        return;
    }
    
    std::cout<< "[";
    const char* comma = "";
    if ((value & static_cast<uint8_t>(CheckFlags::TIME)) !=0) {
        std::cout<< comma << "TIME";
        comma = ",";
    }
    if ((value & static_cast<uint8_t>(CheckFlags::DATE)) !=0) {
        std::cout<< comma << "DATE";
        comma = ",";
    }
    if ((value & static_cast<uint8_t>(CheckFlags::USER)) !=0) {
        std::cout<< comma << "USER";
        comma = ",";
    }
    if ((value & static_cast<uint8_t>(CheckFlags::CERT)) !=0) {
        std::cout<< comma << "CERT";
        comma = ",";
    }
    if ((value & static_cast<uint8_t>(CheckFlags::KEYS)) !=0) {
        std::cout<< comma << "KEYS";
        comma = ",";
    }
    if ((value & static_cast<uint8_t>(CheckFlags::DEST)) !=0) {
        std::cout<< comma << "DEST";
        comma = ",";
    }
    
    std::cout<<"]";
}
