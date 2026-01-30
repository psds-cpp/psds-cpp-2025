#include <cstdint>
#include <iostream>
#include <string>
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

namespace {
    const std::vector<std::pair<CheckFlags, std::string_view>> checkNames = {
        {CheckFlags::TIME, "TIME"},
        {CheckFlags::DATE, "DATE"},
        {CheckFlags::USER, "USER"},
        {CheckFlags::CERT, "CERT"},
        {CheckFlags::KEYS, "KEYS"},
        {CheckFlags::DEST, "DEST"},
    };    
}


void PrintCheckFlags(CheckFlags flags) {
    if (flags > CheckFlags::ALL) { 
        return;
    }

    if (flags == CheckFlags::NONE) {
        std::cout << "[]";
        return;
    }
    
    std::string needed_checks = "[";

    bool first = true;
    for (const auto& [key, val] : checkNames) {
        if (static_cast<uint8_t>(flags) & static_cast<uint8_t>(key)) {
            if (!first) {
                needed_checks += ","; 
            }

            needed_checks += val;
            first = false;
        } 
    }

    needed_checks += "]";

    std::cout << needed_checks;
}
