#include <cstdint>
#include <stdexcept>
#include <string>
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
    if (value > static_cast<uint8_t>(CheckFlags::ALL)){
        return; // Если выходит за диапазон то вывод пустой
    }
    if (value == static_cast<uint8_t>(CheckFlags::NONE)){
        std::cout << "[]";
        return; // Если 0 то пустые кавычки
    }

    std::string check_flags = "[";
    bool first = true;

    if ((value & static_cast<uint8_t>(CheckFlags::TIME)) != 0){
        if (!first) check_flags += ",";
        check_flags += "TIME";
        first = false;
    }
    if ((value & static_cast<uint8_t>(CheckFlags::DATE)) != 0){
        if (!first) check_flags += ",";
        check_flags += "DATE";
        first = false;
    }
    if ((value & static_cast<uint8_t>(CheckFlags::USER)) != 0){
        if (!first) check_flags += ",";
        check_flags += "USER";
        first = false;
    }
    if ((value & static_cast<uint8_t>(CheckFlags::CERT)) != 0){
        if (!first) check_flags += ",";
        check_flags += "CERT";
        first = false;
    }
    if ((value & static_cast<uint8_t>(CheckFlags::KEYS)) != 0){
        if (!first) check_flags += ",";
        check_flags += "KEYS";
        first = false;
    }
    if ((value & static_cast<uint8_t>(CheckFlags::DEST)) != 0){
        if (!first) check_flags += ",";
        check_flags += "DEST";
        first = false;
    }
    check_flags += "]";
    std::cout << check_flags;
}
