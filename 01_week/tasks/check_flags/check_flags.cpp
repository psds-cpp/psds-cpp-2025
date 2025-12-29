#include <cstdint>
#include <string>
#include <utility>
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

CheckFlags operator&(CheckFlags lhs, CheckFlags rhs) {
    return static_cast<CheckFlags>(static_cast<uint8_t>(lhs) & static_cast<uint8_t>(rhs));
}

void PrintCheckFlags(CheckFlags flags) {
    // Проверка на выход за диапозон значений CheckFlags
    if ((~static_cast<uint8_t>(CheckFlags::ALL) & static_cast<uint8_t>(flags)) != 0) {
        return;
    }

    const static std::pair<CheckFlags, std::string> checks[] {
        {CheckFlags::TIME, "TIME"},
        {CheckFlags::DATE, "DATE"},
        {CheckFlags::USER, "USER"},
        {CheckFlags::CERT, "CERT"},
        {CheckFlags::KEYS, "KEYS"},
        {CheckFlags::DEST, "DEST"}
    };

    bool first = true;

    std::cout << "[";

    for (const auto& [flag, name] : checks) {
        if ((flags & flag) != CheckFlags::NONE) {
            if (first) {
                first = false;
            }
            else {
                std::cout << ",";
            }
            std::cout << name;
        }
    }

    std::cout << ']';
}
