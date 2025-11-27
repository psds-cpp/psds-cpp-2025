#include <cstdint>
#include <iostream>
#include <string>

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

void PrintCheckFlags(CheckFlags flags) {
    uint8_t bits = static_cast<uint8_t>(flags);

    if (bits > static_cast<uint8_t>(CheckFlags::ALL)) {
        return;    
    }

    if (bits == static_cast<uint8_t>(CheckFlags::NONE)) {
        std::cout << "[]";
        return;    
    }

    std::string output = "[";

    if (bits & static_cast<uint8_t>(CheckFlags::TIME)) {
        output += "TIME,";
    }
    if (bits & static_cast<uint8_t>(CheckFlags::DATE)) {
        output += "DATE,";
    }
    if (bits & static_cast<uint8_t>(CheckFlags::USER)) {
        output += "USER,";
    }
    if (bits & static_cast<uint8_t>(CheckFlags::CERT)) {
        output += "CERT,";
    }
    if (bits & static_cast<uint8_t>(CheckFlags::KEYS)) {
        output += "KEYS,";
    }
    if (bits & static_cast<uint8_t>(CheckFlags::DEST)) {
        output += "DEST,";
    }

    output.back() = ']';

    std::cout << output;
}
