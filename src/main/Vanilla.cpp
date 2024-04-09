#include "Vanilla.h"

// all the work ha been done by payoff bridge class
VanillaOption::VanillaOption(const PayOffBridge& ThePayOff_, double Expiry_)
: ThePayOff(ThePayOff_), Expiry(Expiry_)
{
    
}


double VanillaOption::GetExpiry() const
{
    return Expiry;
}

double VanillaOption::OptionPayOff(double Spot) const
{
    return ThePayOff(Spot);
}