#include <vector>
#include <stddef.h>


void Filter(std::vector<int>& arr, bool (*filter_func)(int)) {
    if (!filter_func) return;

    size_t j = 0;

    for (size_t i = 0; i < arr.size(); ++i) {
        if (filter_func(arr[i])) {
            arr[j++] = arr[i];
        }
    }

    size_t new_size = j;
    arr.resize(new_size);
}