#include <stdexcept>
#include <iostream>
#include <vector>
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

const size_t max_count_flags = 6;
    
CheckFlags operator|(const CheckFlags& f1, const CheckFlags f2) {
    uint8_t res = 0;
    for (size_t i = 0; i < max_count_flags; ++i) {
        uint8_t b_1 = (static_cast<uint8_t>(f1) >> i) & 1u;
        uint8_t b_2 = (static_cast<uint8_t>(f2) >> i) & 1u;
        if ((b_1 | b_2) == 1) res |= (1u << i); 
    }
    return static_cast<CheckFlags>(res);
}

bool operator&(const CheckFlags& f1, const CheckFlags& f2) {
    if (f1 == CheckFlags::NONE || f2 == CheckFlags::NONE) return false;
    
    bool flag1 = true;
    bool flag2 = true;
    uint8_t res = 0;
    for (size_t i = 0; i < max_count_flags; ++i) {
        uint8_t b_1 = (static_cast<uint8_t>(f1) >> i) & 1u;
        uint8_t b_2 = (static_cast<uint8_t>(f2) >> i) & 1u;
        res |= ((b_1 & b_2) << i);
        if (flag1 && b_1 == 0 && b_2 == 1) flag1 = false;
        if (flag2 && b_1 == 1 && b_2 == 0) flag2 = false;
    }
    if ((static_cast<CheckFlags>(res) == CheckFlags::NONE) || (!flag1 && !flag2)) {
        return false;
    }
    return true;
}

CheckFlags operator^(const CheckFlags& f1, const CheckFlags& f2) {
    uint8_t res = 0;
    for (size_t i = 0; i < max_count_flags; ++i) {
        uint8_t b_1 = (static_cast<uint8_t>(f1) >> i) & 1u;
        uint8_t b_2 = (static_cast<uint8_t>(f2) >> i) & 1u;
        if ((b_1 & b_2) == 0 && (b_1 | b_2) == 1) res |= (1u << i); 
    }
    return static_cast<CheckFlags>(res);
}

CheckFlags operator~(const CheckFlags& f) {
    int8_t res = 0;
    for (size_t i = 0; i < max_count_flags; ++i) {
        uint8_t b = (static_cast<uint8_t>(f) >> i) & 1u;
        if (b == 0) res |= (1u << i); 
    }
    return static_cast<CheckFlags>(res);
}

std::ostream& operator<<(std::ostream& os, const CheckFlags& flags) {
    bool the_first = true;
    std::string str_flags = "";

    if (static_cast<int8_t>(flags) &
        static_cast<int8_t>(CheckFlags::TIME)) {
        str_flags += "TIME";
        the_first = false;
    }
    if (static_cast<int8_t>(flags) &
        static_cast<int8_t>(CheckFlags::DATE)) {
        the_first ? str_flags += "DATE" : str_flags += ", DATE";
        the_first = false;
    }
    if (static_cast<int8_t>(flags) &
        static_cast<int8_t>(CheckFlags::USER) ) {
        the_first ? str_flags += "USER" : str_flags += ", USER";
        the_first = false;
    }
    if (static_cast<int8_t>(flags) &
        static_cast<int8_t>(CheckFlags::CERT)) {
        the_first ? str_flags += "CERT" : str_flags += ", CERT";
        the_first = false;
    }
    if (static_cast<int8_t>(flags) &
        static_cast<int8_t>(CheckFlags::KEYS)) {
        the_first ? str_flags += "KEYS" : str_flags += ", KEYS";
        the_first = false;
    }
    if (static_cast<int8_t>(flags) &
        static_cast<int8_t>(CheckFlags::DEST)) {
        the_first ? str_flags += "DEST" : str_flags += ", DEST";
        the_first = false;
    }
    if (str_flags.length() == 0) str_flags += "NONE";

    os << str_flags;
    
    return os;
}
