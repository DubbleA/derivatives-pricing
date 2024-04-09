#ifndef MC_STATISTICS_H
#define MC_STATISTICS_H

#include <vector>

/*
We want a reusable statistics gatherer. We might have different Monte Carlo routines which would each have unique statistics relevant to evaluating how 
good the model is running. 

The routine should take in data for each path and output desired statistics. 

DumpOneResult: takes in a double and returned nothing. Will dump the result of a single path. will be called once per iteration of loop
GetResultsSoFar: returns results as a 2D vector (table) will be called once per simulation
*/

class StatisticsMC
{
public:
    StatisticsMC(){}
    
    virtual void DumpOneResult(double result)=0; // a pure virtual function
    virtual std::vector<std::vector<double>> GetResultsSoFar()const=0;
    virtual StatisticsMC* clone()const=0;// possibility of virtual copy construction
    virtual ~StatisticsMC(){}//virtual destructor

};

//inherited from StatisticsMC, return mean of simulation
class StatisticsMean:public StatisticsMC
{
public:
    StatisticsMean();
    virtual void DumpOneResult(double result);
    virtual std::vector<std::vector<double>> GetResultsSoFar()const;
    virtual StatisticsMC* clone() const;
    
private:
    double RunningSum;
    unsigned long PathsDone;
};

#endif // end MC_STATISTICS_H