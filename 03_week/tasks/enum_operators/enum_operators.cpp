#include <stdexcept>
#include <vector>
#include <cstdint>
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

CheckFlags operator|(const CheckFlags& lhs, const CheckFlags& rhs) {
    return static_cast<CheckFlags>(
        (static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs)) & 0x3F // Оставим только шесть бит
    );
}

bool operator&(const CheckFlags& lhs, const CheckFlags& rhs) {
    return ((static_cast<uint8_t>(lhs) & 0x3F) & (static_cast<uint8_t>(rhs)& 0x3F)) == (static_cast<uint8_t>(rhs)& 0x3F);
}

CheckFlags operator^(const CheckFlags& lhs, const CheckFlags& rhs) {
    return static_cast<CheckFlags>(
        (static_cast<uint8_t>(lhs) ^ static_cast<uint8_t>(rhs)) & 0x3F // Оставим только шесть бит
    );
}

CheckFlags operator~(const CheckFlags& flag) {
    return static_cast<CheckFlags>(
        (~static_cast<uint8_t>(flag)) & 0x3F
    );
}

std::ostream& operator<<(std::ostream& os, CheckFlags flags) {
    if (flags == CheckFlags::NONE) {
        os << "NONE";
        return os;
    }
    
    
    const std::pair<CheckFlags, std::string> flag_infos[] = {
        {CheckFlags::TIME, "TIME"},
        {CheckFlags::DATE, "DATE"},
        {CheckFlags::USER, "USER"},
        {CheckFlags::CERT, "CERT"},
        {CheckFlags::KEYS, "KEYS"},
        {CheckFlags::DEST, "DEST"}
    };
    
    bool isFirst = true;
    for (const auto& info : flag_infos) {
        if (static_cast<uint8_t>(flags & info.first) != 0) {
            if (!isFirst) os << ", ";
            os << info.second;
            isFirst = false;
        }
    }
    
    return os;
}
