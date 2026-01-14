#include <cstdint>
#include <stdexcept>
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

// В данном случае можно было использовать map, но с ним придется использовать
// static_cast<int>. Так же map отсортирует значения по возрасанию, соответственно
// использовать enum написанный иначе будет невозможно.
const std::vector<std::pair<CheckFlags, std::string_view>> checkNames = {
    {CheckFlags::TIME, "TIME"},
    {CheckFlags::DATE, "DATE"},
    {CheckFlags::USER, "USER"},
    {CheckFlags::CERT, "CERT"},
    {CheckFlags::KEYS, "KEYS"},
    {CheckFlags::DEST, "DEST"},
};

void PrintCheckFlags(CheckFlags flags) {
    if (flags > CheckFlags::ALL) { 
        return;
    }

    std::string needed_checks = "[";

    if (flags == CheckFlags::NONE) {
        needed_checks += "]"; // Такая модификация происходит inplace, не
                              // создавая дорогостоящие копии
        std::cout << needed_checks;
        return;
    }

    bool first = true;
    for (const auto& [key, val] : checkNames) {
        if (static_cast<uint8_t>(flags) & static_cast<uint8_t>(key)) {
            if (!first) {
                needed_checks += ","; // добавляем запятую перед элементом, а не после, 
                                      // проверяя на первый элемент, это гарантирует, что лишних
                                      // запятых не будет
            }

            needed_checks += val;
            first = false;
        } 
    }

    needed_checks += "]";

    std::cout << needed_checks;
}
