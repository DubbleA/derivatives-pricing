#ifndef CONVERGENCE_TABLE_H
#define CONVERGENCE_TABLE_H

#include "MCStatistics.h"
#include "Wrapper.h"

//A convergence table
//In order to get a better feeling of how the simulation is going we might 
//want to have extra statistics for every X or exponential, steps of the simulation, 
//giving us the mean, standard error ... To do so we will store this information in a convergence table.

//We will use this as a gatherer for different statistics gatherers, 
//having the same structure and inhereting from the same base class.

class ConvergenceTable : public StatisticsMC
{
public:
    // constructor, take in a wrapper class which point to a StatisticMC object
    ConvergenceTable(const Wrapper<StatisticsMC>& Inner_);
    
    virtual StatisticsMC* clone() const;
    virtual void DumpOneResult(double result);
    virtual std::vector<std::vector<double>> GetResultsSoFar() const;
    
private:
    Wrapper<StatisticsMC> Inner;
    std::vector<std::vector<double>> ResultSoFar;
    unsigned long StoppingPoint;
    unsigned long PathsDone;
};


#endif // end CONVERGENCE_TABLE_H