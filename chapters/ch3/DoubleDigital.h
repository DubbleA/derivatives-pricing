#ifndef __Option_Class__DoubleDigital__
#define __Option_Class__DoubleDigital__

#include "PayOff2.h"

class PayOffDoubleDigital : public PayOff
{
public:
    PayOffDoubleDigital(double LowerLevel_, double UpperLevel_);
    virtual double operator()(double Spot) const;
    virtual ~PayOffDoubleDigital(){}
    
private:
    double LowerLevel;
    double UpperLevel;
};

#endif /* defined(__Option_Class__DoubleDigital__) */