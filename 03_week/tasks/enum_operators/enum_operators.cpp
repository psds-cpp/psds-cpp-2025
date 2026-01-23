#include <stdexcept>
#include <vector>
#include <ostream>
#include <cstdint>

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

constexpr uint8_t MASK = 0x3F; 
 
inline CheckFlags sanitize(CheckFlags flags) {
    return static_cast<CheckFlags>(static_cast<uint8_t>(flags) & MASK);
}

CheckFlags operator|(CheckFlags lhs, CheckFlags rhs) {
    return static_cast<CheckFlags>(
        (static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs)) & MASK);
}

CheckFlags operator&(CheckFlags lhs, CheckFlags rhs) {
    return static_cast<CheckFlags>(
        (static_cast<uint8_t>(lhs) & static_cast<uint8_t>(rhs)) & MASK);
}

CheckFlags operator^(CheckFlags lhs, CheckFlags rhs) {
    return static_cast<CheckFlags>(
        (static_cast<uint8_t>(lhs) ^ static_cast<uint8_t>(rhs)) & MASK);
}

CheckFlags operator~(CheckFlags flags) {
    return static_cast<CheckFlags>(
        (~static_cast<uint8_t>(flags)) & MASK);
}

std::ostream& operator<<(std::ostream& os, CheckFlags flags) {
    flags = sanitize(flags);
    
    if (flags == CheckFlags::NONE) {
        os << "NONE";
        return os;
    }
    
    bool first = true;
    
    if ((flags & CheckFlags::TIME) != CheckFlags::NONE) {
        os << "TIME";
        first = false;
    }
    
    if ((flags & CheckFlags::DATE) != CheckFlags::NONE) {
        if (!first) os << ", ";
        os << "DATE";
        first = false;
    }
    
    if ((flags & CheckFlags::USER) != CheckFlags::NONE) {
        if (!first) os << ", ";
        os << "USER";
        first = false;
    }
    
    if ((flags & CheckFlags::CERT) != CheckFlags::NONE) {
        if (!first) os << ", ";
        os << "CERT";
        first = false;
    }
    
    if ((flags & CheckFlags::KEYS) != CheckFlags::NONE) {
        if (!first) os << ", ";
        os << "KEYS";
        first = false;
    }
    
    if ((flags & CheckFlags::DEST) != CheckFlags::NONE) {
        if (!first) os << ", ";
        os << "DEST";
    }
    
    return os;
}