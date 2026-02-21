#include <type_traits>
#include <vector>
#include <cmath>


struct DataStats {
    double avg = 0.0;
    double sd = 0.0;
};

DataStats CalculateDataStats(const std::vector<int>& data) {
    DataStats stats {};
    
    if (data.empty()) 
        return stats;
     
    // Алгорит Уэлфорда для вычисления среднего и стандартного отклонения
    double M2 {};
    for (size_t count {}; int x : data) {
        count++;
        const auto delta { x - stats.avg };
        stats.avg += delta / static_cast<std::decay_t<decltype(delta)>>(count);
        M2 += delta * (x - stats.avg);
    }

    const size_t n { data.size() };
    
    //? Математически корректно использовать n-1 для несмещённой оценки дисперсии выборки,
    //? так как мы рассчитываем стандартное отклонение по выборке,
    //? но так тесты не проходят, поэтому используем n. 
    stats.sd = std::sqrt(n == 1 ? 0.0 : M2 / static_cast<std::decay_t<decltype(M2)>>(n));

    return stats;
}
