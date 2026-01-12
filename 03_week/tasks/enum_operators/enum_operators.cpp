#include <stdexcept>
#include <iostream>
#include <sstream>

enum class CheckFlags : u_int8_t
{
    NONE = 0,
    TIME = (1 << 0),
    DATE = (1 << 1),
    USER = (1 << 2),
    CERT = (1 << 3),
    KEYS = (1 << 4),
    DEST = (1 << 5),
    ALL = TIME | DATE | USER | CERT | KEYS | DEST
};

CheckFlags operator|(CheckFlags f, CheckFlags s)
{
    return static_cast<CheckFlags>(((static_cast<u_int8_t>(f) & 0x3F) | (static_cast<u_int8_t>(s) & 0x3F)));
}

bool operator&(CheckFlags f, CheckFlags s)
{
    // Преобразуем в числовые значения
    u_int8_t f_val = static_cast<u_int8_t>(f) & 0x3F;
    u_int8_t s_val = static_cast<u_int8_t>(s) & 0x3F;
    
    // Если один из операндов NONE, возвращаем false
    if (f_val == 0 || s_val == 0)
        return false;
    
    // Проверяем пересечение флагов
    return ((f_val & s_val) ==f_val)||((f_val & s_val)==s_val);
}
CheckFlags operator^(CheckFlags f, CheckFlags s)
{
    return static_cast<CheckFlags>((static_cast<u_int8_t>(f) ^ static_cast<u_int8_t>(s))& 0x3F);
}

CheckFlags operator~(CheckFlags f)
{
    return static_cast<CheckFlags>(~static_cast<u_int8_t>(f)& 0x3F);
}

std::ostream& operator<<(std::ostream& out, CheckFlags flags)
{
    u_int8_t value = static_cast<u_int8_t>(flags) & 0x3F;

    if (value > 0b00111111 || value == static_cast<u_int8_t>(CheckFlags::NONE))
    { // Если установлены биты вне диапазона 0-5
        out << "NONE";
        return out;
    }

    /*if (value == static_cast<u_int8_t>(CheckFlags::ALL))
    {
        out << "CheckFlags::ALL";
        return out;
    }*/

    bool first = true;

    if (static_cast<u_int8_t>(flags) & static_cast<u_int8_t>(CheckFlags::TIME))
    {
        out << "TIME";
        first = false;
    }

    if (static_cast<u_int8_t>(flags) & static_cast<u_int8_t>(CheckFlags::DATE))
    {
        if (!first)
            out << ", ";
        first = false;
        out << "DATE";
    }

    if (static_cast<u_int8_t>(flags) & static_cast<u_int8_t>(CheckFlags::USER))
    {
        if (!first)
            out << ", ";
        first = false;
        out << "USER";
    }

    if (static_cast<u_int8_t>(flags) & static_cast<u_int8_t>(CheckFlags::CERT))
    {
        if (!first)
            out << ", ";
        first = false;
        out << "CERT";
    }

    if (static_cast<u_int8_t>(flags) & static_cast<u_int8_t>(CheckFlags::KEYS))
    {
        if (!first)
            out << ", ";
        first = false;
        out << "KEYS";
    }

    if (static_cast<u_int8_t>(flags) & static_cast<u_int8_t>(CheckFlags::DEST))
    {
        if (!first)
            out << ", ";
        first = false;
        out << "DEST";
    }

    return out;
}
