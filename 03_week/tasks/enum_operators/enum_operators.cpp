#include <cstdint>
#include <iostream>
#include <utility>

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

std::pair<uint8_t, uint8_t> truncate_invalid_flags(CheckFlags lhs, CheckFlags rhs) {
    uint8_t all = static_cast<uint8_t>(CheckFlags::ALL);
    uint8_t left = static_cast<uint8_t>(lhs) & all;
    uint8_t right = static_cast<uint8_t>(rhs) & all;
    return std::pair{left, right};
}

uint8_t truncate_invalid_flags(uint8_t flags) {
    uint8_t all = static_cast<uint8_t>(CheckFlags::ALL);
    uint8_t flags_cleared = flags & all;
    return flags_cleared;
}

CheckFlags operator|(CheckFlags lhs, CheckFlags rhs) {
    auto [left, right] = truncate_invalid_flags(lhs, rhs);
    return static_cast<CheckFlags>(left | right);
}

bool operator&(CheckFlags lhs, CheckFlags rhs) {
    auto [left, right] = truncate_invalid_flags(lhs, rhs);

    if (left == 0u || right == 0u) {
        return false;
    }

    uint8_t result = left & right;
    return (result == left || result == right);
}

CheckFlags operator^(CheckFlags lhs, CheckFlags rhs) {
    auto [left, right] = truncate_invalid_flags(lhs, rhs);
    return static_cast<CheckFlags>(left ^ right);
}

CheckFlags operator~(CheckFlags flags) {
    uint8_t flags_inverted = ~static_cast<int>(flags);
    uint8_t flags_cleared = truncate_invalid_flags(flags_inverted);
    return static_cast<CheckFlags>(flags_cleared);
}

std::ostream& operator<<(std::ostream& os, CheckFlags flags) {
    const static std::pair<CheckFlags, std::string> checks[] {
        {CheckFlags::TIME, "TIME"},
        {CheckFlags::DATE, "DATE"},
        {CheckFlags::USER, "USER"},
        {CheckFlags::CERT, "CERT"},
        {CheckFlags::KEYS, "KEYS"},
        {CheckFlags::DEST, "DEST"}
    };

    bool empty = true;
    bool first = true;

    for (const auto& [flag, name] : checks) {
        uint8_t flags_int = static_cast<int>(flags);
        uint8_t check_int = static_cast<int>(flag);
        CheckFlags single_flag = static_cast<CheckFlags>(flags_int & check_int);
        if (single_flag != CheckFlags::NONE) {
            if (first) {
                first = false;
            }
            else {
                os << ", ";
            }
            os << name;
            empty = false;
        }
    }

    if (empty) {
        os << "NONE";
    }

    return os;
}
