#include <vector>
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

std::string GetFlagName(CheckFlags flags, CheckFlags check) {
    uint8_t flags_int = static_cast<int>(flags);
    uint8_t check_int = static_cast<int>(check);
    CheckFlags single_flag = static_cast<CheckFlags>(flags_int & check_int);

    if (single_flag & CheckFlags::TIME) {
        return "TIME";
    }
    else if (single_flag & CheckFlags::DATE) {
        return "DATE";
    }
    else if (single_flag & CheckFlags::USER) {
        return "USER";
    }
    else if (single_flag & CheckFlags::CERT) {
        return "CERT";
    }
    else if (single_flag & CheckFlags::KEYS) {
        return "KEYS";
    }
    else if (single_flag & CheckFlags::DEST) {
        return "DEST";
    }
    else if (single_flag & CheckFlags::NONE) {
        return "NONE";
    }
    else {
        return "";
    }
}

std::ostream& operator<<(std::ostream& os, CheckFlags flags) {
    std::vector<CheckFlags> checks{
        CheckFlags::TIME, 
        CheckFlags::DATE,
        CheckFlags::USER,
        CheckFlags::CERT,
        CheckFlags::KEYS,
        CheckFlags::DEST,
    };

    std::vector<std::string> flags_names{};
    flags_names.reserve(checks.size());

    for (size_t i = 0; i < checks.size(); ++i) {
        if (flags & checks[i]) {
            flags_names.push_back(GetFlagName(flags, checks[i]));
        }
    }

    if (flags_names.empty()) {
        os << "NONE";
        return os;
    }

    for (size_t i = 0, flags_size = flags_names.size(); i < flags_size; ++i) {
        os << flags_names[i];
        if (i != flags_size - 1) {
            os << ", ";
        }
    }

    return os;
}
