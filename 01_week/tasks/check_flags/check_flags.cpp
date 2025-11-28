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
    const uint8_t valid_mask = 0x3F; // 0b00111111

    if (value & ~valid_mask) {
        std::cout << "";
        return;
    }

    std::string output = "[";
    const char* separator = "";

    auto add_flag = [&](CheckFlags flag, const char* name) {
        if (value & static_cast<uint8_t>(flag)) {
            output += separator;
            output += name;
            separator = ",";
        }
    };

    add_flag(CheckFlags::TIME, "TIME");
    add_flag(CheckFlags::DATE, "DATE");
    add_flag(CheckFlags::USER, "USER");
    add_flag(CheckFlags::CERT, "CERT");
    add_flag(CheckFlags::KEYS, "KEYS");
    add_flag(CheckFlags::DEST, "DEST");

    output += "]";
    std::cout << output;
}