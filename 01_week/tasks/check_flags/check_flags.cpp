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
    uint8_t flags_uint8 = static_cast<uint8_t>(flags);

    //Массив с именами флагов
    std::string flagStr[6] = {"TIME", "DATE", "USER", "CERT", "KEYS", "DEST"};
    //Если флаг больше ALL значит он выходит из диапазона значений флагов
    if (static_cast<uint8_t>(flags) > static_cast<uint8_t>(CheckFlags::ALL)) {
        std::cout << "";
        return;
    }
    //В остальных случаях флаги перебираются и добавляюся в строку если присутствуют 
    uint8_t flag = 1;
    bool str_write = false;
    std::cout << "[";
    for (size_t i = 0; flag < static_cast<uint8_t>(CheckFlags::ALL); ++i) {
        if (flags_uint8 & flag) {
            std::cout <<  (str_write ? "," : "");
            std::cout << flagStr[i];
            str_write = true;
        }
        flag *= 2;
    }

    std::cout << "]";
}
