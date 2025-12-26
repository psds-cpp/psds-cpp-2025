#include <cstdint>
#include <stdexcept>
#include <bits/stdc++.h>


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

    if (value == static_cast<uint8_t>(CheckFlags::NONE)) {
        std::cout << "[]";
        return;
    }
    else if (value >= 1 << 6) {
        std::cout << "";
        return;
    }

    std::cout << "[";

    bool first = true;
    auto try_print = [&](CheckFlags f, const char* name) {
        if (value & static_cast<uint8_t>(f)) {
            if (!first)
                std::cout << ",";
            std::cout << name;
            first = false;
        }
    };

    try_print(CheckFlags::TIME, "TIME");
    try_print(CheckFlags::DATE, "DATE");
    try_print(CheckFlags::USER, "USER");
    try_print(CheckFlags::CERT, "CERT");
    try_print(CheckFlags::KEYS, "KEYS");
    try_print(CheckFlags::DEST, "DEST");

    std::cout << "]";
}
