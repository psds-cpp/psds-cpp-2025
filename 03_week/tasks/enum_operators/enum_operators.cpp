#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
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

// Вспомогательная функция для санитизации флагов (убирает флаги вне диапазона)
inline constexpr CheckFlags sanitize(CheckFlags flags) {
    return static_cast<CheckFlags>(static_cast<uint8_t>(flags) & 
                                   static_cast<uint8_t>(CheckFlags::ALL));
}

// Побитовое ИЛИ
constexpr CheckFlags operator|(CheckFlags lhs, CheckFlags rhs) {
    return sanitize(static_cast<CheckFlags>(
        static_cast<uint8_t>(sanitize(lhs)) | 
        static_cast<uint8_t>(sanitize(rhs))));
}

// Побитовое И (возвращает bool согласно условию)
constexpr bool operator&(CheckFlags lhs, CheckFlags rhs) {
    lhs = sanitize(lhs);
    rhs = sanitize(rhs);
    
    // Если любой из операндов NONE, возвращаем false
    if (lhs == CheckFlags::NONE || rhs == CheckFlags::NONE) {
        return false;
    }
    
    // Проверяем, что один операнд является подмножеством другого
    uint8_t l = static_cast<uint8_t>(lhs);
    uint8_t r = static_cast<uint8_t>(rhs);
    uint8_t intersection = l & r;
    
    // Возвращаем true, если все флаги lhs содержатся в rhs
    // ИЛИ все флаги rhs содержатся в lhs
    return intersection == l || intersection == r;
}

// Исключающее ИЛИ
constexpr CheckFlags operator^(CheckFlags lhs, CheckFlags rhs) {
    return sanitize(static_cast<CheckFlags>(
        static_cast<uint8_t>(sanitize(lhs)) ^ 
        static_cast<uint8_t>(sanitize(rhs))));
}

// Побитовое НЕ (инверсия)
constexpr CheckFlags operator~(CheckFlags flags) {
    return sanitize(static_cast<CheckFlags>(
        static_cast<uint8_t>(CheckFlags::ALL) & 
        ~static_cast<uint8_t>(sanitize(flags))));
}

// Вывод флагов в поток
std::ostream& operator<<(std::ostream& os, CheckFlags flags) {
    flags = sanitize(flags);
    
    if (flags == CheckFlags::NONE) {
        os << "NONE";
        return os;
    }
    
    std::vector<std::string> active_flags;
    
    if (static_cast<uint8_t>(flags & CheckFlags::TIME)) {
        active_flags.push_back("TIME");
    }
    if (static_cast<uint8_t>(flags & CheckFlags::DATE)) {
        active_flags.push_back("DATE");
    }
    if (static_cast<uint8_t>(flags & CheckFlags::USER)) {
        active_flags.push_back("USER");
    }
    if (static_cast<uint8_t>(flags & CheckFlags::CERT)) {
        active_flags.push_back("CERT");
    }
    if (static_cast<uint8_t>(flags & CheckFlags::KEYS)) {
        active_flags.push_back("KEYS");
    }
    if (static_cast<uint8_t>(flags & CheckFlags::DEST)) {
        active_flags.push_back("DEST");
    }
    
    for (size_t i = 0; i < active_flags.size(); ++i) {
        os << active_flags[i];
        if (i != active_flags.size() - 1) {
            os << ", ";
        }
    }
    
    return os;
}