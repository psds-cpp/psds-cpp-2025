#include <stdexcept>
#include <vector>
#include <cmath>


struct DataStats {
    double avg = 0.0;
    double sd = 0.0;
};

DataStats CalculateDataStats(std::vector<int> vector) {
    double avg = 0.0;
    double sko = 0.0;
    size_t size_of_v = vector.size();
    for (int num : vector){
        avg += num; 
    }
    avg = size_of_v > 0 ? avg/size_of_v : 0.0;
    for (int num : vector){
        sko += (num-avg)*(num-avg); 
    }
    sko = size_of_v > 0 ? sqrt(sko / size_of_v) : 0.0;
    return  DataStats{avg, sko};
}
