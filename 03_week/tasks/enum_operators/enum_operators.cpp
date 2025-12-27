#include <stdexcept>
#include <vector>
#include <cstdint>
#include <ostream>

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

// разрешены только младшие 6 бит
inline CheckFlags sanitize(CheckFlags flags) {
    uint8_t value = static_cast<uint8_t>(flags);
    uint8_t all_value = static_cast<uint8_t>(CheckFlags::ALL);
    return static_cast<CheckFlags>(value & all_value);
}

CheckFlags operator|(CheckFlags lhs, CheckFlags rhs) {
    uint8_t result = static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs);
    return sanitize(static_cast<CheckFlags>(result));
}

bool operator&(CheckFlags lhs, CheckFlags rhs) {
    lhs = sanitize(lhs);
    rhs = sanitize(rhs);

    uint8_t lhs_val = static_cast<uint8_t>(lhs);
    uint8_t rhs_val = static_cast<uint8_t>(rhs);
    if (lhs_val == 0 || rhs_val == 0) {
        return false;
    }

    uint8_t common = lhs_val & rhs_val;
    return common == lhs_val || common == rhs_val;
}

CheckFlags operator^(CheckFlags lhs, CheckFlags rhs) {
    uint8_t result = static_cast<uint8_t>(lhs) ^ static_cast<uint8_t>(rhs);
    return sanitize(static_cast<CheckFlags>(result));
}

CheckFlags operator~(CheckFlags flags) {
    uint8_t all_value = static_cast<uint8_t>(CheckFlags::ALL);
    uint8_t value = static_cast<uint8_t>(flags);

    uint8_t result = (~value) & all_value;
    return static_cast<CheckFlags>(result);
}

std::ostream& operator<<(std::ostream& os, CheckFlags flags) {
    flags = sanitize(flags);

    uint8_t value = static_cast<uint8_t>(flags);
    if (value == 0) {
        os << "NONE";
        return os;
    }

    bool first = true;
    if (value & static_cast<uint8_t>(CheckFlags::TIME)) {
        if (!first) os << ", ";
        os << "TIME";
        first = false;
    }
    if (value & static_cast<uint8_t>(CheckFlags::DATE)) {
        if (!first) os << ", ";
        os << "DATE";
        first = false;
    }
    if (value & static_cast<uint8_t>(CheckFlags::USER)) {
        if (!first) os << ", ";
        os << "USER";
        first = false;
    }
    if (value & static_cast<uint8_t>(CheckFlags::CERT)) {
        if (!first) os << ", ";
        os << "CERT";
        first = false;
    }
    if (value & static_cast<uint8_t>(CheckFlags::KEYS)) {
        if (!first) os << ", ";
        os << "KEYS";
        first = false;
    }
    if (value & static_cast<uint8_t>(CheckFlags::DEST)) {
        if (!first) os << ", ";
        os << "DEST";
        first = false;
    }

    return os;
}