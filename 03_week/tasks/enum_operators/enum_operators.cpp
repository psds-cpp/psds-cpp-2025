#include <stdexcept>
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

CheckFlags operator|(CheckFlags flags1, CheckFlags flags2) {
    uint8_t all = static_cast<uint8_t>(CheckFlags::ALL);
    uint8_t value1 = static_cast<uint8_t>(flags1) & all; // Обрезаем все биты слева которые заходят за допустимый размер all
    uint8_t value2 = static_cast<uint8_t>(flags2) & all;
    return static_cast<CheckFlags>(value1 | value2);
}

CheckFlags operator^(CheckFlags flags1, CheckFlags flags2) {
    uint8_t all = static_cast<uint8_t>(CheckFlags::ALL);
    uint8_t value1 = static_cast<uint8_t>(flags1) & all;
    uint8_t value2 = static_cast<uint8_t>(flags2) & all;
    return static_cast<CheckFlags>(value1 ^ value2); // побитовый xor для двух чисел и последующий каст
}


bool operator&(CheckFlags flags1, CheckFlags flags2) {
    uint8_t all = static_cast<uint8_t>(CheckFlags::ALL);
    uint8_t value1 = static_cast<uint8_t>(flags1) & all;
    uint8_t value2 = static_cast<uint8_t>(flags2) & all;
    if (value1 == static_cast<uint8_t>(CheckFlags::NONE) || value2 == static_cast<uint8_t>(CheckFlags::NONE)) return false;
    return ((value1 & value2) == value1) || ((value1 & value2) == value2); // проверка является один из операндов подмножеством другого

}

CheckFlags operator~(CheckFlags flags) {
    uint8_t all = static_cast<uint8_t>(CheckFlags::ALL);
    uint8_t value = static_cast<uint8_t>(flags);
    value = (value == static_cast<uint8_t>(CheckFlags::NONE)) ? static_cast<uint8_t>(CheckFlags::ALL) : ~value; // если NONE то перевод в ALL если нет то инвертируем
    return static_cast<CheckFlags>(value & all); // Обрезаем все биты слева которые заходят за допустимый размер all
}

std::ostream& operator<<(std::ostream& os, const CheckFlags& flags) {
    uint8_t all = static_cast<uint8_t>(CheckFlags::ALL);
    uint8_t value = static_cast<uint8_t>(flags) & all; // Обрезаем все биты слева которые заходят за допустимый размер all

    if (value == static_cast<uint8_t>(CheckFlags::NONE)){
        os << "NONE";
        return os;
    }

    bool first = true; // Если вывод флага первый, то перед ним запятая не ставится
// ПРоверка наличия каждого флага в flags
    if ((value & static_cast<uint8_t>(CheckFlags::TIME)) != 0){
        if (!first) os << ", "; // Если вывод не первый, то перед ним ставится запятая
        os << "TIME";
        first = false;
    }
    if ((value & static_cast<uint8_t>(CheckFlags::DATE)) != 0){
        if (!first) os << ", ";
        os << "DATE";
        first = false;
    }
    if ((value & static_cast<uint8_t>(CheckFlags::USER)) != 0){
        if (!first) os << ", ";
        os << "USER";
        first = false;
    }
    if ((value & static_cast<uint8_t>(CheckFlags::CERT)) != 0){
        if (!first) os << ", ";
        os << "CERT";
        first = false;
    }
    if ((value & static_cast<uint8_t>(CheckFlags::KEYS)) != 0){
        if (!first) os << ", ";
        os << "KEYS";
        first = false;
    }
    if ((value & static_cast<uint8_t>(CheckFlags::DEST)) != 0){
        if (!first) os << ", ";
        os << "DEST";
        first = false;
    }
    return os;
}
