#include <atomic>
#include <cstdint>
#include <iterator>
#include <ostream>
#include <stdatomic.h>
#include <sys/types.h>
#include <type_traits>
#include <vector>

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

const std::vector<std::pair<CheckFlags, std::string_view>> checkNames = {
    {CheckFlags::TIME, "TIME"},
    {CheckFlags::DATE, "DATE"},
    {CheckFlags::USER, "USER"},
    {CheckFlags::CERT, "CERT"},
    {CheckFlags::KEYS, "KEYS"},
    {CheckFlags::DEST, "DEST"},
};

std::underlying_type_t<CheckFlags> getVal(CheckFlags f) {
    return static_cast<std::underlying_type_t<CheckFlags>>(f) &
        static_cast<std::underlying_type_t<CheckFlags>>(CheckFlags::ALL);
}

bool operator!(const CheckFlags f) {
    return getVal(f) == 0;
}

bool operator==(CheckFlags lhs, CheckFlags rhs) {
    return getVal(lhs) == getVal(rhs);
}

bool operator!=(CheckFlags lhs, CheckFlags rhs) {
    return !(lhs == rhs);
}

CheckFlags operator|(CheckFlags lhs, CheckFlags rhs) {
    return static_cast<CheckFlags>((getVal(lhs) | getVal(rhs)) & getVal(CheckFlags::ALL));
}

bool operator&(CheckFlags lhs, CheckFlags rhs) {
    auto lhsVal = getVal(lhs);
    auto rhsVal = getVal(rhs);

    if (lhsVal == 0 || rhsVal == 0) {
        return false;
    }
    
    return ((lhsVal & rhsVal) == lhsVal) || ((lhsVal & rhsVal) == rhsVal);
}

CheckFlags operator^(CheckFlags lhs, CheckFlags rhs) {
    return static_cast<CheckFlags>((getVal(lhs) ^ getVal(rhs)) & getVal(CheckFlags::ALL));
}

CheckFlags operator~(const CheckFlags& f) {
    return static_cast<CheckFlags>((~getVal(f)) & getVal(CheckFlags::ALL));
}

std::ostream& operator<<(std::ostream& os, const CheckFlags& f) {
    std::string needed_checks = "";

    auto fVal = getVal(f);

    if (f == CheckFlags::NONE) {
        os << "NONE";
        return os;
    }

    bool first = true;
    for (const auto& [key, val] : checkNames) {
        if (fVal & getVal(key)) {
            if (!first) {
                needed_checks += ", ";
            }

            needed_checks += val;
            first = false;
        } 
    }

    os << needed_checks;
    return os;
}
