#include <stdexcept>
#include <vector>

std::vector<size_t> FindAll(const std::vector<int>& data, bool (*func)(int))
{
    std::vector<size_t> found;
    if (func && !data.empty())
    {
        size_t counter = 0;
        for (size_t i = 0; i < data.size(); ++i)
        {
            if (func(data[i]))
            {
                found.push_back(i);
                ++counter;
            }
        }
        found.resize(counter);
        found.shrink_to_fit();
    }
    return found;
}