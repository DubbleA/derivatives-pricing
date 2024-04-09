#ifndef PARAMETERS_H
#define PARAMETERS_H

/*
 store parameters such as volatility, IR, general setup: jump intensity.
 need to return the integral or integral sqaure over any time interval
 
 use bridge design: class Parameter point to an abstract class: ParametersInner

 allows easy extension of variable Parameters without actually putting them in
 */

/*
The mean method returns the average value of the parameter between two times
Implemented by calling the Integral method which does all the work. 

The RMS method returns the root-mean-square of the parameter between two times. The rms of the volatility
is what we use in our Black Scholes formula when volatility is variable. 

The rest of the code works similarly to our PayOff class. We give one inherited class, the simplest possible one, 
ParametersConstant, which enacts a constant parameter. As well as storing the value of the constant, we also store
its square in order to minimize time spent computing the square integral. Time can be saved by computing values
which may be needed repeatedly, once and for all in the constructor. 
*/

/*


*/

class ParametersInner
{
public:
    ParametersInner(){}
    
    virtual ParametersInner* clone() const=0;
    virtual double Integral(double time1, double time2) const=0;
    virtual double IntegralSquare(double time1, double time2) const=0;
    virtual ~ParametersInner(){}
private:
};

class Parameters
{
public:
    Parameters(const ParametersInner& innerObject);
    Parameters(const Parameters& orignial);
    Parameters& operator=(const Parameters& original);
    virtual ~Parameters();
    
    inline double Integral(double time1, double time2) const;
    inline double IntegralSquare(double time1, double time2) const;
    double Mean(double time1, double time2)const;
    double RootMeanSquare(double time1, double time2) const;
    
private:
    ParametersInner* InnerObjectPtr; // a bridge class
};

inline double Parameters::Integral(double time1, double time2)const
{
    // call method in ParameterInner instance
    return InnerObjectPtr->Integral(time1,time2);
}

inline double Parameters::IntegralSquare(double time1, double time2)const
{
    return InnerObjectPtr->IntegralSquare(time1, time2);
}

// inheritant from ParameterInner class
class ParametersConstant:public ParametersInner
{
public:
    ParametersConstant(double constant);
    
    virtual ParametersInner* clone() const;
    virtual double Integral(double time1,double time2) const;
    virtual double IntegralSquare(double time1, double time2) const;
    
private:
    double Constant;
    double ConstantSquare;
};

#endif //end PARAMETERS_H