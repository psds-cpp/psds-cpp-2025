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


static constexpr const uint8_t ALL_FLAGS { static_cast<uint8_t>(CheckFlags::ALL) };

static constexpr CheckFlags RemoveOverflows(const CheckFlags flags) {
    return static_cast<CheckFlags>(static_cast<uint8_t>(flags) & ALL_FLAGS);
}


auto operator|(const CheckFlags lhs, const CheckFlags rhs) {
    return RemoveOverflows(static_cast<CheckFlags>(
        static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs)));
}

auto operator&(const CheckFlags lhs, const CheckFlags rhs) {
    const uint8_t l { static_cast<uint8_t>(RemoveOverflows(lhs)) };
    const uint8_t r { static_cast<uint8_t>(RemoveOverflows(rhs)) };
    
    if (l == 0 || r == 0) return false;                // любые проверки с NONE -> false

    const uint8_t inter { static_cast<uint8_t>(l & r) };
    const bool lhs_subset_rhs { (inter == l) };        // все биты lhs содержатся в rhs
    const bool rhs_subset_lhs { (inter == r) };        // все биты rhs содержатся в lhs

    return lhs_subset_rhs || rhs_subset_lhs;

}

auto operator^(const CheckFlags lhs, const CheckFlags rhs) {
    return RemoveOverflows(static_cast<CheckFlags>(
        static_cast<uint8_t>(lhs) ^ static_cast<uint8_t>(rhs)));

}

auto operator~(const CheckFlags flags) {
    const uint8_t val { static_cast<uint8_t>(flags) };
    return RemoveOverflows(static_cast<CheckFlags>(~val));
}

auto operator<<(std::ostream& os, const CheckFlags flags) -> std::ostream& {
    const uint8_t value { static_cast<uint8_t>(RemoveOverflows(flags)) };

    if (value == 0) {
        os << "NONE";
        return os;
    }

    bool first { true };
    auto print_flag = [&](CheckFlags f, const char* name) {
        if ((static_cast<uint8_t>(flags) & static_cast<uint8_t>(f)) != 0) {
            if (!first) os << ", ";
            os << name;
            first = false;
        }
    };

    print_flag(CheckFlags::TIME, "TIME");
    print_flag(CheckFlags::DATE, "DATE");
    print_flag(CheckFlags::USER, "USER");
    print_flag(CheckFlags::CERT, "CERT");
    print_flag(CheckFlags::KEYS, "KEYS");
    print_flag(CheckFlags::DEST, "DEST");

    return os;
}
