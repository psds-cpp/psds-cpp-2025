#include <cstddef>

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

namespace {
    uint8_t all_uint8 = static_cast<uint8_t>(CheckFlags::ALL);
}

CheckFlags operator|(const CheckFlags& lhs, const CheckFlags& rhs) {
    uint8_t res = static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs);
    res = res & all_uint8;
    return static_cast<CheckFlags>(res);
}

bool operator&(const CheckFlags& lhs, const CheckFlags& rhs) { 
    uint8_t lhs_uint8 = static_cast<uint8_t>(lhs) & all_uint8;
    uint8_t rhs_uint8 = static_cast<uint8_t>(rhs) & all_uint8;
    if(lhs_uint8 == 0 || rhs_uint8 == 0) return false;
    return ((lhs_uint8 & rhs_uint8) == lhs_uint8) || ((lhs_uint8 & rhs_uint8) == rhs_uint8);
}

CheckFlags operator^(const CheckFlags& lhs, const CheckFlags& rhs) {
    uint8_t lhs_uint8 = static_cast<uint8_t>(lhs) & all_uint8;
    uint8_t rhs_uint8 = static_cast<uint8_t>(rhs) & all_uint8;
    return static_cast<CheckFlags>(lhs_uint8 ^ rhs_uint8);
}

CheckFlags operator~(const CheckFlags& flags) {
    return static_cast<CheckFlags>(~(static_cast<uint8_t>(flags)) & all_uint8);
}

std::ostream& operator<<(std::ostream& os, const CheckFlags& flags) {
    uint8_t flags_uint8 = static_cast<uint8_t>(flags);
    if(static_cast<uint8_t>(flags_uint8 << 2) == 0){
        os << "NONE";
        return os;
    }

    //Массив с именами флагов
    std::string flagStr[6] = {"TIME", "DATE", "USER", "CERT", "KEYS", "DEST"};
    uint8_t flag = 1;
    bool str_write = false;
    for (size_t i = 0; flag < all_uint8; ++i) {
        if (flags_uint8 & flag) {
            os <<  (str_write ? ", " : "");
            os << flagStr[i];
            str_write = true;
        }
        flag *= 2;
    }

    return os;
}
