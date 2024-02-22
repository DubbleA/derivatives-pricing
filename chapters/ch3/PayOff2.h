#ifndef __Option_Class__PayOff2__
#define __Option_Class__PayOff2__

#include <iostream>

//base class
class PayOff 
{
public:
    PayOff(){};
    // pure virtual function doesn't need to be defined in base class
    virtual double operator()(double Spot) const = 0;
    virtual ~PayOff(){}
    
private:
    
};


class PayOffCall: public PayOff
{
public:
    PayOffCall(double Strike_);
    virtual double operator()(double Spot) const; //given spot, return payoff
    virtual ~PayOffCall(){}
    
private:
    double Strike;
};


class PayOffPut: public PayOff
{
public:
    PayOffPut(double Strike_);
    virtual double operator()(double Spot) const;
    virtual ~PayOffPut(){}
    
private:
    double Strike;
    
};
#endif /* defined(__Option_Class__PayOff2__) */