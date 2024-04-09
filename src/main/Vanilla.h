#ifndef VANILLA_H
#define VANILLA_H

#include "PayOffBridge.h"

/*
Vanilla Option class
Designed to be copied/moved to any other class and utilizes code already written for the PayOff class
so we have no uncessary duplication. 

*/

class VanillaOption
{
public:
    VanillaOption(const PayOffBridge& ThePayOff_,double Expiry);
    double OptionPayOff(double Spot) const;
    double GetExpiry() const;
    
private:
    double Expiry;
    PayOffBridge ThePayOff;
};

#endif // VANILLA_H