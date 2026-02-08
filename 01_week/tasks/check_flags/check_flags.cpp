#include <cstdint>
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
    if (flags == CheckFlags::NONE) {
        std::cout << "[]";
        return;
    }

    if ((static_cast<uint8_t>(flags) & ~static_cast<uint8_t>(CheckFlags::ALL)) != 0) {
        std::cout << "";
        return;
    }

    std::cout << "[";
    bool first = true;
    if ((static_cast<uint8_t>(flags) & static_cast<uint8_t>(CheckFlags::TIME)) != 0) {
        if (!first) std::cout << ",";
        std::cout << "TIME";
        first = false;
    }
    if ((static_cast<uint8_t>(flags) & static_cast<uint8_t>(CheckFlags::DATE)) != 0) {
        if (!first) std::cout << ",";
        std::cout << "DATE";
        first = false;
    }
    if ((static_cast<uint8_t>(flags) & static_cast<uint8_t>(CheckFlags::USER)) != 0) {
        if (!first) std::cout << ",";
        std::cout << "USER";
        first = false;
    }
    if ((static_cast<uint8_t>(flags) & static_cast<uint8_t>(CheckFlags::CERT)) != 0) {
        if (!first) std::cout << ",";
        std::cout << "CERT";
        first = false;
    }
    if ((static_cast<uint8_t>(flags) & static_cast<uint8_t>(CheckFlags::KEYS)) != 0) {
        if (!first) std::cout << ",";
        std::cout << "KEYS";
        first = false;
    }
    if ((static_cast<uint8_t>(flags) & static_cast<uint8_t>(CheckFlags::DEST)) != 0) {
        if (!first) std::cout << ",";
        std::cout << "DEST";
        first = false;
    }
    std::cout << "]";
}
