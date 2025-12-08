#include <iomanip>

void PrintMemory(int value, bool reverse = false) {
    using std::cout, std::hex, std::uppercase, std::setw, std::setfill;
    // Представляем как массив байт
    const uint8_t* bytes = reinterpret_cast<const uint8_t*>(&value);

    cout << "0x";
    cout << uppercase << hex;
    if (reverse) {
        // Печатаем от старших к младшим
        for (int i = sizeof(int) - 1; i >= 0; --i) {
            cout << setw(2)
                << setfill('0') << static_cast<int>(bytes[i]);
        }
    }
    else {
		// Печатаем от младших к старшим
        for (size_t i = 0; i < sizeof(int); ++i) {
            cout << setw(2)
                << setfill('0') << static_cast<int>(bytes[i]);
        }
    }
    cout << "\n";
}

void PrintMemory(double value, bool reverse = false) {
    using std::cout, std::hex, std::uppercase, std::setw, std::setfill;
    const uint8_t* bytes = reinterpret_cast<const uint8_t*>(&value);

    cout << "0x";
    cout << uppercase << hex;
    if (reverse) {
        // Печатаем от старших к младшим
        for (int i = sizeof(double) - 1; i >= 0; --i) {
            cout << setw(2)
                << setfill('0') << static_cast<int>(bytes[i]);
        }
    }
    else {
		// Печатаем от младших к старшим
        for (size_t i = 0; i < sizeof(double); ++i) {
            cout << setw(2)
                << setfill('0') << static_cast<int>(bytes[i]);
        }
    }
    cout << "\n";
}
