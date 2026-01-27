#include <stdexcept>
#include <vector>
#include <tuple>

std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator> MinMax(const std::vector<int> &data)
{

    if (!data.empty())
    {
        std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator> counters = {data.cbegin(), data.cbegin()};
        size_t size = data.size();

        for (size_t i = 0; i < size; ++i)
        {
            std::vector<int>::const_iterator it = data.cbegin() + i;
            if (*it < *counters.first)
            {
                counters.first = it;
            }
            else
            {
                if (*it >= *counters.second)
                {
                    counters.second = it;
                }
            }
        }

        return counters;
    }
    else
    {
        std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator> counters;
        return counters;
    }
}
