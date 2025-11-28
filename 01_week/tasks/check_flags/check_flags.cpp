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
    uint8_t all_bits = static_cast<uint8_t>(CheckFlags::ALL);

    // выход за пределы возможных значений
    if (value & ~all_bits) {
        return;
    }

    // не установлено никаких флагов
    if (value == 0) {
        std::cout << "[]";
        return;
    }

    const std::pair<CheckFlags, const char*> flag_names[] = {
        {CheckFlags::TIME, "TIME"},
        {CheckFlags::DATE, "DATE"},
        {CheckFlags::USER, "USER"},
        {CheckFlags::CERT, "CERT"},
        {CheckFlags::KEYS, "KEYS"},
        {CheckFlags::DEST, "DEST"}
    };

    bool first = true;
    std::cout << "[";
    for (const auto& flag : flag_names) {
        if (value & static_cast<uint8_t>(flag.first)) {
            if (!first) {
                std::cout << ",";
            }
            std::cout << flag.second;
            first = false;
        }
    }
    std::cout << "]";
}