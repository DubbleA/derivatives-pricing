#include "DoubleDigital.h"

PayOffDoubleDigital::PayOffDoubleDigital(double LowerLevel_, double Upperlevel_)
: LowerLevel(LowerLevel_), UpperLevel(Upperlevel_)
{
    
}

double PayOffDoubleDigital::operator()(double Spot) const
{
    return (LowerLevel <= Spot && Spot <= UpperLevel) ? 1 : 0;
}