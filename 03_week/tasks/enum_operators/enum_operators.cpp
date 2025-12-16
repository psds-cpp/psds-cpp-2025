#include <cstdint>
#include <stdexcept>
#include <bits/stdc++.h>
#include <sys/types.h>

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

constexpr uint8_t flagAll = static_cast<uint8_t>(CheckFlags::ALL);

constexpr uint8_t toUi(CheckFlags flag) {
    return static_cast<uint8_t>(flag) & flagAll;
}

constexpr CheckFlags operator|(CheckFlags lFlag, CheckFlags rFlag) {
    return static_cast<CheckFlags>(toUi(lFlag) | toUi(rFlag));
}

constexpr bool operator&(CheckFlags lFlag, CheckFlags rFlag) {
    uint8_t lFlagUi = toUi(lFlag);
    uint8_t rFlagUi = toUi(rFlag);

    if (lFlagUi == 0 || rFlagUi == 0)
        return false;

    return (lFlagUi & rFlagUi) == lFlagUi || (lFlagUi & rFlagUi) == rFlagUi;
}

constexpr CheckFlags operator^(CheckFlags lFlag, CheckFlags rFlag) {
    return static_cast<CheckFlags>(toUi(lFlag) ^ toUi(rFlag));
}

constexpr CheckFlags operator~(CheckFlags flag) {
    return static_cast<CheckFlags>(flagAll & ~toUi(flag));
}

std::ostream& operator<<(std::ostream& os, CheckFlags flag) {
    uint8_t num = toUi(flag);
    bool first = true;
    auto try_print = [&](CheckFlags f, const char* name) {
        if (num & toUi(f)) {
            if (!first)
                os << ", ";
            os << name;
            first = false;
        }
    };

    try_print(CheckFlags::TIME, "TIME");
    try_print(CheckFlags::DATE, "DATE");
    try_print(CheckFlags::USER, "USER");
    try_print(CheckFlags::CERT, "CERT");
    try_print(CheckFlags::KEYS, "KEYS");
    try_print(CheckFlags::DEST, "DEST");

    if (first)
        os << "NONE";

    return os;
}
