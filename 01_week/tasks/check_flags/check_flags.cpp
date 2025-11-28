#include <cstdint>
#include <string>
#include <vector>
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

CheckFlags operator&(CheckFlags lhs, CheckFlags rhs) {
    return static_cast<CheckFlags>(static_cast<uint8_t>(lhs) & static_cast<uint8_t>(rhs));
}

std::string GetFlagName(CheckFlags flags) {
    switch (flags) {
        case CheckFlags::TIME:
            return "TIME";
        case CheckFlags::DATE:
            return "DATE";
        case CheckFlags::USER:
            return "USER";
        case CheckFlags::CERT:
            return "CERT";
        case CheckFlags::KEYS:
            return "KEYS";
        case CheckFlags::DEST:
            return "DEST";
        default:
            return "";
    }
}

void PrintCheckFlags(CheckFlags flags) {
    // Проверка на выход за диапозон значений CheckFlags
    if (static_cast<int>(CheckFlags::ALL) < static_cast<int>(flags)) {
        return;
    }

    std::vector<CheckFlags> checks{
        CheckFlags::TIME, 
        CheckFlags::DATE,
        CheckFlags::USER,
        CheckFlags::CERT,
        CheckFlags::KEYS,
        CheckFlags::DEST,
    };

    std::vector<std::string> flags_names{};
    for (auto &check : checks) {
        if (std::string flag_name = GetFlagName(flags & check); flag_name != "") {
            flags_names.push_back(flag_name);
        }
    }

    std::string result = "[";
    for (size_t i = 0, flags_size = flags_names.size(); i < flags_size; ++i) {
        result += flags_names[i];
        if (i != flags_size - 1) {
            result += ',';
        }
    }
    std::cout << result << ']';
}
