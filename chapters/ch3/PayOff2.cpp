#include "PayOff2.h"
#include <algorithm> // for max() function

PayOffCall::PayOffCall(double strike_): Strike(strike_)
{
    
}

double PayOffCall::operator()(double Spot) const
{
    return std::max(Spot - Strike,0.0);
    
}

PayOffPut::PayOffPut(double Strike_):Strike(Strike_)
{
    
}

double PayOffPut::operator()(double Spot) const
{
    return std::max(Strike - Spot,0.0);
}