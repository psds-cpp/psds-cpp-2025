#include <iostream>
#include <iomanip>


void PrintMemory(int num, bool is_little_endian = false) {
    const u_char* begin = reinterpret_cast<u_char*>(&num);
    const u_char* end = reinterpret_cast<u_char*>(&num) + sizeof(num);

    std::cout << "0x" << std::hex << std::uppercase;
    if (is_little_endian) {
        for (const u_char* ptr = end - 1; ptr >= begin; --ptr) {
            std::cout << std::setfill('0') << std::setw(2) << static_cast<int>(*ptr);
        }
    }
    else {
        for (const u_char* ptr = begin; ptr < end; ++ptr) {
            std::cout << std::setfill('0') << std::setw(2) << static_cast<int>(*ptr);
        }
    }
    std::cout << std::endl;
}

void PrintMemory(double num, bool is_little_endian = false) {
    const u_char* begin = reinterpret_cast<u_char*>(&num);
    const u_char* end = reinterpret_cast<u_char*>(&num) + sizeof(num);

    std::cout << "0x" << std::hex << std::uppercase;
    if (is_little_endian) {
        for (const u_char* ptr = end - 1; ptr >= begin; --ptr) {
            std::cout << std::setfill('0') << std::setw(2) << static_cast<int>(*ptr);
        }
    }
    else {
        for (const u_char* ptr = begin; ptr < end; ++ptr) {
            std::cout << std::setfill('0') << std::setw(2) << static_cast<int>(*ptr);
        }
    }
    std::cout << std::endl;
}
