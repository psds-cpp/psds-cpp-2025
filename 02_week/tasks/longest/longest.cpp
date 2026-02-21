const char* FindLongestSubsequence(const char* begin, const char* end, size_t& count) {
    if (!begin || !end || begin >= end) {
        count = 0;
        return nullptr;
    }

    const char* longestStringStart = begin;
    size_t longestStringLength = 1;
    const char* currentStart = begin;
    size_t currentLength = 1;
    const char* previousCharacter = begin;
    const char* currentCharacter = begin + 1;

    for (; currentCharacter < end; ++currentCharacter) {
        if (*currentCharacter == *previousCharacter) {
            currentLength++;
        }
        else {
            if (currentLength > longestStringLength) {
                longestStringLength = currentLength;
                longestStringStart = currentStart;
            }
            currentStart = currentCharacter;
            currentLength = 1;
        }
        previousCharacter = currentCharacter;
    }

    // Проверка последнего сегмента
    if (currentLength > longestStringLength) {
        longestStringLength = currentLength;
        longestStringStart = currentStart;
    }

    count = longestStringLength;
    return longestStringStart;
}

char* FindLongestSubsequence(char* begin, char* end, size_t& count) {
    return const_cast<char*>(
        FindLongestSubsequence(static_cast<const char*>(begin),
            static_cast<const char*>(end),
            count)
        );
}

