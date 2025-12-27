void PrintArray(nullptr_t, nullptr_t, size_t = 0) {
    std::cout << "[]\n";
}

template <typename T>
void PrintArray(const T* begin, const T* end, size_t limit = 0) {
    using std::cout;
    if (begin == nullptr || end == nullptr || begin == end) {
        cout << "[]\n";
        return;
    }

    bool reversed = end < begin;
    const T* first = begin;
    const T* last = end;


	size_t count = abs(static_cast<ptrdiff_t>(last - first)); // количество элементов в массиве

    // Печать без ограничений по количеству элементов
	cout << "[";
    if (limit == 0 || limit >= count) {
        if (reversed == false) {
            for (const T* ptr = first; ptr != last; ++ptr) {
                if (ptr != first) cout << ", ";
                cout << *ptr;
            }
        }
        else {
			for (const T* ptr = first; ptr != last; --ptr) {
                if (ptr != first) cout << ", ";
                cout << *ptr;
            }
        }
		cout << "]\n";
        return;
    }


    // Печать с ограничениями
    size_t printed = 0;
    const T* ptr = first;

    while (printed < count) {
        size_t onLine = 0;

        while (onLine < limit && printed < count) {
            if (onLine > 0) cout << ", ";
            cout << *ptr;
            ++onLine;
            ++printed;
            ptr += reversed ? -1 : 1;
        }

        // Не все символы смогли напечатать на одной строке, переносим
        if (printed < count) {
            cout << ", ...\n";
            cout << " ";
        }
    }

    cout << "]\n";
}