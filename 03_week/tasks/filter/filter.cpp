#include <stdexcept>
#include <vector>

void Filter(std::vector<int> &data, bool (*func)(int))
{
    if (!data.empty() && func != nullptr)
    {
        size_t counter = 0;
       
        for (size_t i = 0; i < data.size(); ++i)
        {
            if (func(data[i]))
            {
                if (i!= counter){
                    data[counter] = data[i];
                }
                ++counter;
            }
        }   
        data.resize(counter);
    }
    return;
}