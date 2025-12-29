#include <iostream>
#include <iomanip>

void PrintMemory(const u_char* begin, size_t size, bool is_little_endian) {
    const u_char* end = begin + size;

    std::cout << "0x" << std::hex << std::uppercase;
        for (
            const u_char* ptr = is_little_endian ? end - 1 : begin;
            is_little_endian ? ptr >= begin : ptr < end;
            is_little_endian ? --ptr : ++ptr
        ) {
            std::cout << std::setfill('0') << std::setw(2) << static_cast<int>(*ptr);
        }
    std::cout << std::endl;
}

void PrintMemory(int num, bool is_little_endian = false) {
    PrintMemory(reinterpret_cast<u_char*>(&num), sizeof(num), is_little_endian);
}

void PrintMemory(double num, bool is_little_endian = false) {
    PrintMemory(reinterpret_cast<u_char*>(&num), sizeof(num), is_little_endian);
}
