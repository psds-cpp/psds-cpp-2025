#include <stdexcept>
#include <vector>
#include <math.h>

struct DataStats {
    double avg = 0.0;
    double sd = 0.0;
};

struct DataStats CalculateDataStats(std::vector<int> data) {
   
    struct DataStats output;
    if (data.empty()){
        output.avg = 0.;
        output.sd = 0.;
        return output;
    }

    /*
    стандартная девиация считается как sqrt(сумма((i - avg)^2)/size)
    если разложим квадратное уравнение: sqrt(сумма(i^2 - 2*i*avg + avg^2)/size)=>
    sqrt((сумма(i^2)+ сумма(- 2* i*avg)+сумма(avg^2))/size) - его имплементируем
    */
    
    double first_num = 0.;
    double second_num= 0.;

    for (size_t i=0; i< data.size(); ++i){
        output.avg+=data[i];
        first_num += static_cast<double>(data[i])*static_cast<double>(data[i]);
        second_num+= data[i]; 
    }
    output.avg /= data.size();
    output.sd = first_num - 2. * second_num * output.avg + output.avg * output.avg * data.size();
    output.sd /= data.size();
    output.sd = sqrt(output.sd);
    return output;
}
