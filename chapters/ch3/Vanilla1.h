//
//  Vanilla1\.h
//  Option_Class
//
//  Created by cheerzzh on 10/6/14.
//  Copyright (c) 2014年 Jared Zhou. All rights reserved.
//

#ifndef __Option_Class__Vanilla1___
#define __Option_Class__Vanilla1___

#include <iostream>
#include "PayOff2.h" // use payoff class


// want the vanilla option to store copy of payoff object
class VanillaOption
{
public:
    VanillaOption(PayOff& ThePayOff_, double Expiry_);
    double GetExpiry() const; // return the expiry of the option
    double OptionPayOff(double Spot) const; // return the payoff given spot
    
private:
    double Expiry;
    PayOff& ThePayOff;
};


#endif /* defined(__Option_Class__Vanilla1___) */